#pragma once

#include <string>
#include <thread>
#include <future>
#include <mutex>
#include <deque>
#include <random>
#include <algorithm>
#include <fmt/format.h>

#include "cppzmq_incl.hpp"

class networker_t {
private:
  std::atomic_bool app_running;
  std::mutex internal_mutex;

  int own_port;
  std::string own_address;
  std::deque<std::string> peers;

  std::deque<std::string> incoming_messages;
  std::deque<std::string> outgoing_messages;

  std::future<void> future_incoming_worker;
  std::future<void> future_outgoing_worker;

public:
  networker_t() {
    fmt::print("networker constructed\n");
    auto _ = std::unique_lock(internal_mutex);

    std::random_device rdev;
    std::mt19937 mtgen(rdev());
    std::uniform_int_distribution<> distrib(-100, 100);
    own_port = 5678 + distrib(mtgen);
    own_address = fmt::format("tcp://127.0.0.1:{}", own_port);

    app_running.store(true);

    future_incoming_worker =
      std::async(std::launch::async, &networker_t::incoming_work, this);
    future_outgoing_worker =
      std::async(std::launch::async, &networker_t::outgoing_work, this);

    fmt::print("own addr: {}", own_address);
  }
  ~networker_t() {
    app_running.store(false);
    future_incoming_worker.get();
    future_outgoing_worker.get();
    fmt::print("networker destructed\n");
  }

public:
  std::string getaddr() {
    auto _ = std::unique_lock(internal_mutex);
    return own_address;
  }
  void setport(int port) {
    auto _ = std::unique_lock(internal_mutex);
    own_port = port;
    own_address = fmt::format("tcp://127.0.0.1:{}", own_port);
  }

  void addpeer(std::string peer) {
    auto _ = std::unique_lock(internal_mutex);
    peers.push_back(peer);
  }
  void rempeer(std::string peer) {
    auto _ = std::unique_lock(internal_mutex);
    peers.erase(std::remove(peers.begin(), peers.end(), peer), peers.end());
  }

  std::vector<std::string> readmess() {
    auto _ = std::unique_lock(internal_mutex);

    std::vector<std::string> output_messages;

    while (!incoming_messages.empty()) {
      output_messages.push_back(incoming_messages.back());
      incoming_messages.pop_back();
    }

    return output_messages;
  }
  void sendmess(std::string message) {
    auto _ = std::unique_lock(internal_mutex);
    outgoing_messages.push_back(message);
  }

  std::deque<std::string> listpeers() {
    auto _ = std::unique_lock(internal_mutex);
    return peers;
  }

private:
  void incoming_work();
  void outgoing_work();
};
