
#include <chrono>
#include <thread>
#include <future>
#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.hpp>

#include "latch.hpp"

//
// these tests check if the threads are running in correct order
// (and waiting, and are getting released)
// through the use of a std::vector<std::string>
// and also std::async with its std::future::get
// and checking if elements are asynchronously being written
// into the vector in the correct order
//

TEST_CASE("Wait and Release, with 1 thread")
{
    std::vector<std::string> vec;
    auto vec_push_back =
        [&](std::string _x) {
            static std::mutex mut;
            std::unique_lock lock(mut);
            vec.push_back(_x);
        };

    bok::Latch<1> latch;
    vec_push_back("main start");

    auto async1 = std::async(
        [&]() {
            latch.Wait();
            vec_push_back("async after waiting");
        });

    vec_push_back("main before release");
    CHECK(vec.size() == 2);
    latch.Release();
    async1.get();

    vec_push_back("main after release");

    CHECK(vec[0] == "main start");
    CHECK(vec[1] == "main before release");
    CHECK(vec[2] == "async after waiting");
    CHECK(vec[3] == "main after release");
}
TEST_CASE("Wait and Release, with 2 threads")
{
    std::vector<std::string> vec;
    auto vec_push_back =
        [&](std::string _x) {
            static std::mutex mut;
            std::unique_lock lock(mut);
            vec.push_back(_x);
        };

    bok::Latch<2> latch;
    vec_push_back("main start");

    auto async1 = std::async(
        [&]() {
            latch.Wait();
            vec_push_back("async1 after waiting");
        });
    auto async2 = std::async(
        [&]() {
            latch.Wait();
            vec_push_back("async2 after waiting");
        });

    vec_push_back("main before release");
    CHECK(vec.size() == 2);
    latch.Release();
    async1.get();
    async2.get();

    vec_push_back("main after release");

    CHECK(vec[0] == "main start");
    CHECK(vec[1] == "main before release");
    CHECK((vec[2] == "async1 after waiting" || vec[2] == "async2 after waiting"));
    CHECK((vec[3] == "async1 after waiting" || vec[3] == "async2 after waiting"));
    CHECK(vec[4] == "main after release");
}
TEST_CASE("Wait and Release, with n threads")
{
    const int n = 24;

    std::vector<std::string> vec;
    auto vec_push_back =
        [&](std::string _x) {
            static std::mutex mut;
            std::unique_lock lock(mut);
            vec.push_back(_x);
        };

    bok::Latch<9999> latch;
    vec_push_back("main start");

    std::vector<std::future<void>> futures;
    for (int i = 0; i < n; i++)
        futures.push_back(std::async(
            [&]() {
                latch.Wait();
                vec_push_back("async after waiting");
            }));

    vec_push_back("main before release");
    CHECK(vec.size() == 2);
    latch.Release();
    for (auto &fut : futures)
        fut.get();

    vec_push_back("main after release");

    CHECK(vec[0] == "main start");
    CHECK(vec[1] == "main before release");
    for (int i = 0; i < n; i++)
        CHECK(vec[2 + i] == "async after waiting");
    CHECK(vec[2 + n] == "main after release");
}
TEST_CASE("Arrive, with 2 threads")
{
    std::vector<std::string> vec;
    auto vec_push_back =
        [&](std::string _x) {
            static std::mutex mut;
            std::unique_lock lock(mut);
            vec.push_back(_x);
        };

    bok::Latch<2> latch;
    vec_push_back("main start");

    auto async1 = std::async(
        [&]() {
            vec_push_back("async1 before arrival");
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            latch.Arrive();
            vec_push_back("async1 after waiting");
        });
    auto async2 = std::async(
        [&]() {
            vec_push_back("async2 before arrival");
            latch.Arrive();
            vec_push_back("async2 after waiting");
        });

    async1.get();
    async2.get();

    vec_push_back("main after releases");

    INFO(vec[0] + ", " + vec[1] + ", " + vec[2] + ", " + vec[3] + ", " + vec[4] + ", " + vec[5]);
    CHECK(vec[0] == "main start");
    CHECK((vec[1] == "async1 before arrival" || vec[1] == "async2 before arrival"));
    CHECK((vec[2] == "async1 before arrival" || vec[2] == "async2 before arrival"));
    CHECK((vec[3] == "async1 after waiting" || vec[3] == "async2 after waiting"));
    CHECK((vec[4] == "async1 after waiting" || vec[4] == "async2 after waiting"));
    CHECK(vec[5] == "main after releases");
}
TEST_CASE("Decrement, with 2 threads")
{
    std::vector<std::string> vec;
    auto vec_push_back =
        [&](std::string _x) {
            static std::mutex mut;
            std::unique_lock lock(mut);
            vec.push_back(_x);
        };

    bok::Latch<> latch_async;
    bok::Latch<2> latch_callback;
    vec_push_back("main start");

    auto async1 = std::async(
        [&]() {
            latch_async.Wait();
            vec_push_back("async1 after waiting");
            latch_callback.Decrement();
        });
    auto async2 = std::async(
        [&]() {
            latch_async.Wait();
            vec_push_back("async2 after waiting");
            latch_callback.Decrement();
        });

    vec_push_back("main before async release");
    latch_async.Release();

    latch_callback.Wait();
    vec_push_back("main after callback decrement");

    async1.get();
    async2.get();

    vec_push_back("main after async[1..2].get()");

    CHECK(vec[0] == "main start");
    CHECK(vec[1] == "main before async release");
    CHECK((vec[2] == "async1 after waiting" || vec[2] == "async2 after waiting"));
    CHECK((vec[3] == "async1 after waiting" || vec[3] == "async2 after waiting"));
    CHECK(vec[4] == "main after callback decrement");
    CHECK(vec[5] == "main after async[1..2].get()");
}
TEST_CASE("Wait and Arrive with callback")
{
    std::vector<std::string> vec;
    auto vec_push_back =
        [&](std::string _x) {
            static std::mutex mut;
            std::unique_lock lock(mut);
            vec.push_back(_x);
        };

    bok::Latch<1> latch;
    vec_push_back("main start");

    auto async1 = std::async(
        [&]() {
            latch.Wait([&]() { vec_push_back("async calls back"); });
            vec_push_back("async after waiting");
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    vec_push_back("main before arrival");
    CHECK(vec.size() == 3);

    latch.Arrive([&]() { vec_push_back("main calls back"); });
    async1.get();

    vec_push_back("main at end");

    CHECK(vec[0] == "main start");
    CHECK(vec[1] == "async calls back");
    CHECK(vec[2] == "main before arrival");
    CHECK((vec[3] == "async after waiting" || vec[3] == "main calls back"));
    CHECK((vec[4] == "async after waiting" || vec[4] == "main calls back"));
    CHECK(vec[5] == "main at end");
}
