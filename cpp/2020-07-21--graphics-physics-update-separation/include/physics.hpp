#pragma once

#include <chrono>
#include "common.hpp"

struct World {
  Updatable m_updatable;
  Vec2f m_position;
  bool m_moving_right;

  World(decltype(m_updatable.update_after_ms) _update_after_ms);
};

void UpdatePhysics(World& _world);
