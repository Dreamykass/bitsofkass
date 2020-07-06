
#include "aqueue.hpp"
#include <future>
#include <chrono>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.hpp>

TEST_CASE("AccessQueue::LockedPayload") {
	bok::AccessQueue<int> aqueue(0);

	auto lpayload = aqueue.GetPriorityAccess();
	CHECK(!lpayload.Empty());
	CHECK(aqueue.Occupied());

	decltype(lpayload) lpay2;
	CHECK(lpay2.Empty());

	lpay2 = std::move(lpayload);
	CHECK(!lpay2.Empty());
	CHECK(lpayload.Empty());
	CHECK(aqueue.Occupied());

	decltype(lpay2) lpay3(std::move(lpay2));
	CHECK(!lpay3.Empty());
	CHECK(lpay2.Empty());
	CHECK(lpayload.Empty());
	CHECK(aqueue.Occupied());

	lpay3.Unlock();
	CHECK(!lpay3.Empty());
	CHECK(!aqueue.Occupied());

	lpay3.LockAgain();
	CHECK(!lpay3.Empty());
	CHECK(aqueue.Occupied());

	lpay3.Clear();
	CHECK(lpay3.Empty());
	CHECK(!aqueue.Occupied());

	{
		auto lpay4 = aqueue.GetPriorityAccess();
		CHECK(!lpay4.Empty());
		CHECK(aqueue.Occupied());
	}
	CHECK(!aqueue.Occupied());

}

TEST_CASE("AccessQueue::GetPriorityAccess()") {
	bok::AccessQueue<int> aqueue(0);
	CHECK(aqueue.UnsafeGet() == 0);

	aqueue.UnsafeGet() = 1;
	CHECK(aqueue.UnsafeGet() == 1);

	auto async1 = std::async(std::launch::async, [&]() { auto l = aqueue.GetPriorityAccess(); *l += 1; });
	auto async2 = std::async(std::launch::async, [&]() { auto l = aqueue.GetPriorityAccess(); *l += 1; });
	auto async3 = std::async(std::launch::async, [&]() { auto l = aqueue.GetPriorityAccess(); *l += 1; });

	async1.get();
	async2.get();
	async3.get();

	CHECK(aqueue.UnsafeGet() == 4);
}

TEST_CASE("AccessQueue::GetAccess()") {
	std::vector<std::string> vec;
	auto vec_push_back =
		[&](std::string _x) {
		static std::mutex mut;
		std::unique_lock lock(mut);
		vec.push_back(_x);
	};

	bok::AccessQueue<int> aqueue(1);
	CHECK(aqueue.UnsafeGet() == 1);

	bok::Latch<> latch;

	auto async0 = std::async(std::launch::async, [&]() { vec_push_back("0"); auto l = aqueue.GetAccess(); *l += 1; latch.Wait();  *l = 10; });
	auto async1 = std::async(std::launch::async, [&]() { vec_push_back("1"); auto l = aqueue.GetAccess(); *l += 1; });
	auto async2 = std::async(std::launch::async, [&]() { vec_push_back("2"); auto l = aqueue.GetAccess(); *l += 1; });
	auto async3 = std::async(std::launch::async, [&]() { vec_push_back("3"); auto l = aqueue.GetAccess(); *l += 1; });

	CHECK(aqueue.Length() == 3);

	CHECK(async0.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready);
	CHECK(async1.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready);
	CHECK(async2.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready);
	CHECK(async3.wait_for(std::chrono::milliseconds(1)) != std::future_status::ready);

	CHECK(aqueue.UnsafeGet() == 2);
	CHECK(aqueue.Length() == 3);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	latch.Release();

	async0.get();
	async1.get();
	async2.get();
	async3.get();

	CHECK(aqueue.UnsafeGet() == 13);

	CHECK(vec[0] == "0");
	CHECK(vec[1] == "1");
	CHECK(vec[2] == "2");
	CHECK(vec[3] == "3");
}
