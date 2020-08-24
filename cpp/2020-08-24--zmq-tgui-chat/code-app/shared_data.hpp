#pragma once

#include <atomic>
#include <thread>
#include <random>
#include <concurrentqueue/blockingconcurrentqueue.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include "misc.hpp"

struct SharedData {
  std::atomic_bool app_should_close;

  safe_string own_ip;
  safe_string own_port;

  moodycamel::BlockingConcurrentQueue<int> bq;

  SharedData() {
    app_should_close.store(false);

    std::random_device rdev;
    std::mt19937 mtgen(rdev());
    std::uniform_int_distribution<> distr(-100, 100);
    own_ip.store("127.0.0.1");
    own_port.store(fmt::to_string(5678 + distr(mtgen)));

    SPDLOG_INFO("own address: {}", GetOwnAddress());
  }

  std::string GetOwnAddress() {
    return fmt::format("tcp://{}:{}", own_ip.load(), own_port.load());
  }
};
