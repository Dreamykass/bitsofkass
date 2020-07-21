#pragma once

#include <chrono>
#include "common.hpp"

struct Window {
  Updatable updatable;

  Window(decltype(updatable.update_on_target) _update_on_target);
};

struct World;

void UpdateGraphics(const World& _world, Window& _window);
