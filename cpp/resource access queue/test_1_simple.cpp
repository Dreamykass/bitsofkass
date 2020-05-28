
#include "aqueue.hpp"
#include <future>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.hpp>

TEST_CASE("") {
	aq::AccessQueue<int> aqueue;
	REQUIRE(aqueue.Length() == 0);
	REQUIRE(aqueue.Occupied() == false);

	aqueue.UnsafeGet() = 16;
	REQUIRE(aqueue.UnsafeGet() == 16);

	SUBCASE("LockedPayload, unlocking and locking, move assignment and construction") {
		auto lpayload = aqueue.GetAccess();
		CHECK(aqueue.Occupied());

		lpayload.Unlock();
		CHECK(!aqueue.Occupied());

		lpayload.LockAgain();
		CHECK(aqueue.Occupied());

		lpayload.Unlock();
		CHECK(!aqueue.Occupied());

		decltype(lpayload) l2 = std::move(lpayload);
		l2.LockAgain();
		CHECK(aqueue.Occupied());
		CHECK(*l2 == 16);
		CHECK(lpayload.Empty());

		{
			decltype(l2) l3(std::move(l2));
			CHECK(aqueue.Occupied());
			CHECK(*l3 == 16);
			CHECK(&*l2 == nullptr);
		}

		CHECK(!aqueue.Occupied());
	}

	SUBCASE("get one access, check occupancy") {
		SUBCASE("GetPriorityAccess") {
			auto lpayload = aqueue.GetPriorityAccess();
			CHECK(*lpayload == 16);
			CHECK(aqueue.Occupied() == true);
			CHECK(aqueue.Length() == 0);

			lpayload.Unlock();
			CHECK(aqueue.Occupied() == false);
			CHECK(aqueue.Length() == 0);
		}

		SUBCASE("GetAccess") {
			auto lpayload = aqueue.GetAccess();
			CHECK(*lpayload == 16);
			CHECK(aqueue.Occupied() == true);
			CHECK(aqueue.Length() == 0);

			lpayload.Unlock();
			CHECK(aqueue.Occupied() == false);
			CHECK(aqueue.Length() == 0);
		}
	}

	SUBCASE("get access twice, the second time async") {
		SUBCASE("GetPriorityAccess") {
			//auto lpayload = aqueue.GetPriorityAccess();
			//CHECK(aqueue.Occupied() == true);
			//CHECK(aqueue.Length() == 0);

			//auto lpayloadpromise = std::async(std::launch::async, &decltype(aqueue)::GetPriorityAccess, &aqueue);
			//CHECK(lpayloadpromise.valid() == false);
			//CHECK(aqueue.Occupied() == true);
			//CHECK(aqueue.Length() == 0);

			//lpayload.Unlock();
			//CHECK(aqueue.Occupied() == true);
			//CHECK(aqueue.Length() == 0);

			//auto lpayload2 = lpayloadpromise.get();
			//CHECK(aqueue.Occupied() == true);
			//CHECK(aqueue.Length() == 0);

			//lpayload2.Unlock();
			//CHECK(aqueue.Occupied() == false);
			//CHECK(aqueue.Length() == 0);
		}

		SUBCASE("GetPriorityAccess") {

		}

		SUBCASE("GetAccess") {

		}
	}

	SUBCASE("thrice") {
		//SUBCASE("") {
		//	auto lp = aqueue.GetBypassedAccess();
		//	CHECK(lp.payload == 16);
		//}

		//SUBCASE("") {
		//	auto lp = aqueue.GetPriorityAccess();
		//	CHECK(lp.payload == 16);
		//}

		//SUBCASE("") {
		//	auto lp = aqueue.GetAccess();
		//	CHECK(lp.payload == 16);
		//}
	}
}