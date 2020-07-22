
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "common.hpp"
#include "physics.hpp"
#include "graphics.hpp"

int main() {
  using namespace std::literals::chrono_literals;

  std::cout << "hello\n";

  std::chrono::steady_clock clock;
  World world(32ms);
  Window window(16ms);

  bool open = true;
  while (open) {
    auto time_now = clock.now();

    if (world.m_updatable.Ready(time_now)) {
      UpdatePhysics(world);
    }

    if (window.m_updatable.Ready(time_now)) {
      UpdateGraphics(world, window, open);
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  std::cout << "bye\n";
  return 0;
}

// todo: do this, but with coroutines!
