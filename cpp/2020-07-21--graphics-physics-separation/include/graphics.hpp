#pragma once

#include <chrono>
#include "common.hpp"

struct Window {
  Updatable updatable;

  Window(decltype(updatable.update_after_ms) _update_after_ms);
};

struct World;

void UpdateGraphics(const World& _world, Window& _window);
