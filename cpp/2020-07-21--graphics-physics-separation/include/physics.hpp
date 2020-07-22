#pragma once

#include <chrono>
#include "common.hpp"

struct World {
  Updatable updatable;
  Vec2f pos;

  World(decltype(updatable.update_after_ms) _update_after_ms);
};

void UpdatePhysics(World& _world);
