#pragma once

#include <chrono>

struct Updatable {
  decltype(std::chrono::steady_clock::now()) update_last;
  const std::chrono::milliseconds update_after_ms;

  Updatable(decltype(update_after_ms) _update_after_ms)
    : update_after_ms(_update_after_ms)
    , update_last(std::chrono::milliseconds(0)) {}

  bool Ready(const decltype(update_last) _time_now) {
    using namespace std::chrono;

    auto time_since_last_update =
      duration_cast<milliseconds>(_time_now - update_last);

    if (time_since_last_update > update_after_ms) {
      update_last = _time_now;
      return true;
    } else {
      return false;
    }
  }
};

struct Vec2f {
  float x;
  float y;
};
