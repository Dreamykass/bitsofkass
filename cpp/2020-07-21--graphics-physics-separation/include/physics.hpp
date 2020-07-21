#pragma once

#include <chrono>
#include "common.hpp"

struct World {
  Updatable updatable;
  Vec2f pos;

  World(decltype(updatable.update_on_target) _update_on_target);
};

void UpdatePhysics(World& _world);
