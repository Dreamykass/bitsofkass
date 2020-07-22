
#include <iostream>
#include <string>
#include <chrono>

#include "common.hpp"
#include "physics.hpp"
#include "graphics.hpp"

int main() {
  using namespace std::literals::chrono_literals;

  std::cout << "hello\n";

  std::chrono::steady_clock clock;
  World world(2000ms);
  Window window(1000ms);

  while (true) {
    auto time_now = clock.now();

    if (world.updatable.Ready(time_now)) {
      UpdatePhysics(world);
      std::cout << "--updated physics/world\n";
    }

    if (window.updatable.Ready(time_now)) {
      UpdateGraphics(world, window);
      std::cout << "--updated graphics/window\n";
    }
  }

  std::cout << "bye\n";
  return 0;
}

// todo: do this, but with coroutines!
