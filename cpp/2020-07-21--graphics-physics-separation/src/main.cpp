
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
  World world(10ms);
  Window window(100ms);

  while (true) {
    auto time = clock.now();
  }

  std::cout << "bye\n";
  return 0;
}

// todo: do this, but with coroutines!
