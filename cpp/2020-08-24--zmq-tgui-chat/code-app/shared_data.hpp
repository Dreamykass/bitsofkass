#pragma once

#include <atomic>
#include <thread>
#include <random>
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <concurrentqueue/concurrentqueue.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include "event_internal.hpp"
#include "misc.hpp"

struct SharedData {

  std::atomic_bool app_should_close;

  SafeString own_ip;
  SafeString own_port;
  SafeString own_name;

  moodycamel::ConcurrentQueue<evi::EventInternal> events_for_gui;
  moodycamel::ConcurrentQueue<evi::EventInternal> events_for_incoming;
  moodycamel::BlockingConcurrentQueue<evi::EventInternal> events_for_outgoing;

  SharedData() {
    app_should_close.store(false);

    std::random_device rdev;
    std::mt19937 mtgen(rdev());
    std::uniform_int_distribution<> distr(-100, 100);
    own_ip.Store("127.0.0.1");
    own_port.Store(fmt::to_string(5678 + distr(mtgen)));
    own_name.Store(fmt::format("anonymous{}", distr(mtgen) + 101));

    SPDLOG_INFO("own address: {}", GetOwnAddress());
    SPDLOG_INFO("own name: {}", own_name.Load());
  }

  std::string GetOwnAddress() {
    return fmt::format("tcp://{}:{}", own_ip.Load(), own_port.Load());
  }
};
