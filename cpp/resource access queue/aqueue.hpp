#pragma once

#include <mutex>
#include <queue>
#include <list>
#include <utility>
#include <latch.hpp>

namespace bok {
	// class that allows thread-safe exclusive access to a resource, in queued manner
	// - resource, meaning the object of the type that the class is instanced with
	// - queued, meaning that access to the resource is provided in queued manner
	//   that is, threads are served access in the order of requests - first in, first out
	// - exclusive, meaning that at a time, only one thread can access the resource
	//   and the thread that's next in the queue will be able to access it, only after the first one is done
	// \n
	// it is non-copyable, non-movable
	template<typename Payload> class AccessQueue {
	public:
		// helper class that is returned by AccessQueue::GetAccess and ::GetPriorityAccess
		// internally, it is just { Payload*; std::unique_lock<std::mutex>; }
		// it allows exclusive access to the resource, meaning that only no other thread
		// can access the resource, until it is unlocked (either manually, or by leaving scope)
		// \n
		// it is movable, but not copyable
		// has star and arrow operator overloads - UB if resource is not locked or empty
		class LockedPayload {
		private:
			Payload* m_payload;
			std::unique_lock<std::mutex> m_lock;

		public:
			// constructs an empty LockedPayload
			LockedPayload() : m_payload(nullptr) {};
			// LockedPayload adopts the lock (it is moved inside)
			LockedPayload(Payload& _payload, std::unique_lock<std::mutex> _mutex)
				: m_payload(&_payload), m_lock(std::move(_mutex)) {}

			LockedPayload(const LockedPayload& other) = delete;
			LockedPayload(LockedPayload&& other) noexcept {
				m_payload = other.m_payload;
				other.m_payload = nullptr;
				//m_lock = std::move(other.m_lock);
				m_lock.swap(other.m_lock);
			}

			LockedPayload& operator=(const LockedPayload& other) = delete;
			LockedPayload& operator=(LockedPayload&& other) noexcept {
				m_payload = other.m_payload;
				other.m_payload = nullptr;
				//m_lock = std::move(other.m_lock);
				m_lock.swap(other.m_lock);
				return *this;
			}

		public:
			const Payload& operator*() const {
				return m_payload;
			}
			const Payload* const operator->() const {
				return &m_payload;
			}
			Payload& operator*() {
				return *m_payload;
			}
			Payload* const operator->() {
				return m_payload;
			}

			// manually unlocks (the mutex that's guarding) the resource,
			// effectively allowing the AccessQueue to give access 
			// to the thread that's next in the queue (if there's any)
			// if the lock is already unlocked, it's UB
			void Unlock() {
				m_lock.unlock();
			}

			// manually locks (the mutex that's guarding) the resource,
			// effectively bypassing the queue
			// if the lock is already unlocked, it's UB
			void LockAgain() {
				m_lock.lock();
			}

			// true if LockedPayload has a resource
			// (and the mutex that's guarding it)
			// false otherwise
			bool Empty() {
				if (m_payload == nullptr)
					return true;
				else
					return false;
			}

			// drops/nulls the lock and the resource, effectively the
			// same as moving an empty LockedPayload into the object
			void Clear() {
				m_payload = nullptr;
				m_lock = decltype(m_lock)();
			}
		};

	private:
		// the resource
		Payload m_payload;
		// mutex guarding the resource, that's returned (via LockedPayload) from Get(Priority)Access
		// and unlocked after the caller is done with the resource
		std::mutex m_payload_mx;

		// mutex guarding the access to the queue, providing thread-safe container operations
		std::mutex m_queue_mx;
		// the queue that holds bok::Latch (basically same as std::latch that will come with C++20)
		// (the internal container is std::list, because bok::Latch is non-movable and non-copyable)
		std::queue<bok::Latch<>, std::list<bok::Latch<>>> m_queue;

	public:
		AccessQueue(Payload&& _payload) {
			m_payload = std::move(_payload);
		}
		~AccessQueue() {}

		AccessQueue(const AccessQueue& other) = delete;
		AccessQueue(AccessQueue&& other) noexcept = delete;

		AccessQueue& operator=(const AccessQueue& other) = delete;
		AccessQueue& operator=(AccessQueue&& other) noexcept = delete;

	public:
		// returns bool from the occupancy of the resource,
		// true if the payload is occupied (and the mutex is locked),
		// false if the payload is not occupied (and the mutex is unlocked)
		// does not guarantee 100% accuracy
		bool Occupied() noexcept {
			std::unique_lock payload_lock(m_payload_mx, std::defer_lock);
			return !payload_lock.try_lock();
		}

		// returns size_t from the length of the queue,
		// does not guarantee 100% accuracy
		size_t Length() noexcept {
			std::unique_lock queue_lock(m_queue_mx);
			auto size = m_queue.size();
			return size;
		}

		// returns the resource managed by the AccessQueue,
		// with no regards to the queue or any thread safety
		Payload& UnsafeGet() noexcept {
			return m_payload;
		}

		// returns LockedPayload,
		// composed from the managed resource and the mutex that guards it
		// bypasses the access queue completely, and instead
		// just tries to lock the mutex that's guarding the payload
		LockedPayload GetPriorityAccess() {
			// lock the payload
			// (and now that the payload is locked...)
			// if the queue is not empty, wake up the thread at the front
			// return

			std::unique_lock payload_lock(m_payload_mx);

			std::unique_lock queue_lock(m_queue_mx);

			if (!m_queue.empty()) {
				m_queue.front().Release();
			}

			return LockedPayload(m_payload, std::move(payload_lock));
		}

		// returns LockedPayload,
		// composed from the managed resource and the mutex that guards it
		// waits properly for access,
		// gets put into the back of the queue
		LockedPayload GetAccess() {
			// lock the queue
			// if the queue is not empty
			//     push a latch to queue,
			//     wait on the latch, with a callback that unlocks the queue
			//     pop the latch from the queue (as now that the caller was notified it is its turn)
			// else
			//     unlock the queue
			// endif
			// 
			// (now it's the caller's turn to wait on the payload)
			// lock the payload
			// 
			// (now the caller has locked the payload)
			// lock the queue
			// if the queue is not empty
			//     release the thread at the front of the queue
			// 
			// fin (this comment thing is outdated)

			std::unique_lock queue_lock(m_queue_mx);
			std::unique_lock payload_lock(m_payload_mx, std::defer_lock);

			if (!m_queue.empty()) {
				m_queue.emplace();
				m_queue.back().Wait([&queue_lock]() {queue_lock.unlock(); });
				m_queue.pop();
				queue_lock.lock();
				payload_lock.lock();
			}
			else if (!payload_lock.try_lock()) {
				m_queue.emplace();
				m_queue.back().Wait([&queue_lock]() {queue_lock.unlock(); });
				m_queue.pop();
				queue_lock.lock();
				payload_lock.lock();
			}

			if (!m_queue.empty()) {
				m_queue.front().Release();
			}

			return LockedPayload(m_payload, std::move(payload_lock));
		}

	};
}