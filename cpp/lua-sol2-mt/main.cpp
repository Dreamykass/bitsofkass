
#define SOL_ALL_SAFETIES_ON 1

#include "sol.hpp"
#include <assert.h>
#include <chrono>
#include <future>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <utility>

void safe_writer(std::string str) {
  static std::mutex mutex;
  std::unique_lock lock(mutex);
  std::cout << str;
}

int random() {
  static thread_local std::random_device rd;
  static thread_local std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distrib(1, 100);
  return distrib(gen);
}

int main() {
  safe_writer("\n\n#################### hello!");

  std::vector<std::future<void>> futures;

  for (int i = 0; i < 4; i++) {
    futures.push_back(std::async(
      std::launch::async,
      [](int i) {
        sol::state temp_state;
        temp_state.open_libraries(sol::lib::base, sol::lib::os);
        temp_state.script_file("worker.lua");
        temp_state["MutexedWriter"] = &safe_writer; // passing a function to lua
        temp_state["Random"] = &random;             // passing a function to lua
        temp_state["Writings"](i);                  // calling lua function
      },
      i));
  }

  for (int i = 0; i < 7; i++) {
    safe_writer("\n[MAIN SAYS " + std::to_string(i) + "]");
    std::this_thread::sleep_for(std::chrono::microseconds(5));
  }

  for (auto& f : futures) {
    f.get();
  }

  safe_writer("\n#################### bye...\n");
  return 0;
}
