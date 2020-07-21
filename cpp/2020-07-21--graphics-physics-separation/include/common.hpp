#pragma once

struct Updatable {
  std::chrono::milliseconds update_last;
  decltype(update_last) update_on_target;

  Updatable(decltype(update_on_target) _update_on_target)
    : update_on_target(_update_on_target)
    , update_last(std::chrono::milliseconds(0)) {}

  bool Ready(decltype(std::chrono::steady_clock::now()) _time_now) {}
};

struct Vec2f {
  float x;
  float y;
};
