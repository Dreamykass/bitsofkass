#pragma once

#include <mutex>

#include <queue>
#include <list>
#include <utility>

namespace aq {
	template<typename Payload> class AccessQueue {
	public:
		struct LockedPayload {
		private:
			Payload* payload;
			std::unique_lock<std::mutex> lock;

		public:
			// constructs an empty LockedPayload
			LockedPayload() : payload(nullptr) {};
			// LockedPayload adopts the lock
			LockedPayload(Payload& _payload, std::mutex& _mutex)
				: payload(&_payload), lock(_mutex, std::adopt_lock) {}

			LockedPayload(const LockedPayload& other) = delete;
			LockedPayload(LockedPayload&& other) noexcept {
				payload = other.payload;
				other.payload = nullptr;
				lock.swap(other.lock);
			}

			LockedPayload& operator=(const LockedPayload& other) = delete;
			LockedPayload& operator=(LockedPayload&& other) noexcept {
				payload = other.payload;
				other.payload = nullptr;
				lock.swap(other.lock);
				return *this;
			}

		public:
			const Payload& operator*() const {
				return payload;
			}
			const Payload* const operator->() const {
				return &payload;
			}
			Payload& operator*() {
				return *payload;
			}
			Payload* const operator->() {
				return payload;
			}

			void Unlock() {
				lock.unlock();
			}
			void LockAgain() {
				lock.lock();
			}
			bool Empty() {
				if (payload == nullptr)
					return true;
				else
					return false;
			}
		};

	private:
		Payload payload;
		std::mutex payload_mx;

		std::mutex queue_mx;
		//std::queue<std::latch, std::list<std::latch>> queue;

	public:
		AccessQueue() {}
		~AccessQueue() {}

		AccessQueue(const AccessQueue& other) = delete;
		AccessQueue(AccessQueue&& other) noexcept = delete;

		AccessQueue& operator=(const AccessQueue& other) = delete;
		AccessQueue& operator=(AccessQueue&& other) noexcept = delete;

	public:
		// returns bool,
		// true if the payload is occupied (and the mutex is locked),
		// false if the payload is not occupied (and the mutex is unlocked)
		bool Occupied() noexcept {
			std::unique_lock queue_lock(queue_mx);
			std::unique_lock payload_lock(payload_mx, std::defer_lock);
			return !payload_lock.try_lock();
		}

		// returns size_t,
		// 
		size_t Length() noexcept {
			std::unique_lock queue_lock(queue_mx);
			return queue.size();
		}

		// returns Payload&,
		// with no regards to the access queue or any thread safety
		Payload& UnsafeGet() {
			return payload;
		}

		// returns {Payload&; std::unique_lock<std::mutex>;},
		// bypasses the access queue completely,
		// just tries to lock the mutex that's guarding the payload
		LockedPayload GetPriorityAccess() {
			payload_mx.lock();
			return LockedPayload(payload, payload_mx);
		}

		// returns {Payload&; std::unique_lock<std::mutex>;},
		// waits properly for access,
		// gets put into the back of the queue
		LockedPayload GetAccess() {
			std::unique_lock queue_lock(queue_mx);

			//if()


			// queue is empty
			//if (payload_mx.try_lock()) {
			//	return return LockedPayload(payload, payload_mx);
			//} // this logic is bad - should check if Length is 0 or something
			  // also should queue.front().notify() if Length is non-zero, after lock?
			// queue is not empty
			//else {
				// // push a latch, and wait on it until awoken
				// queue.push_back(std::latch());
				// std::latch& latch = queue.back();
				// queue_mx.unlock();
				// latch.wait();

				// // awoken now by another thread
				// queue_lock.lock();
				// queue.pop_front();
				// queue.front().notify();
				// payload_mx.lock(); // todo: change it so LockedPayload adopts the payload_mx
				// return LockedPayload(payload, payload_mx);
			//}
		}

	private:

	};
}