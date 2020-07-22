
#include "physics.hpp"

World::World(decltype(m_updatable.update_after_ms) _update_after_ms)
  : m_updatable(_update_after_ms) {

  m_position.x = 0.0f;
  m_position.y = 0.0f;
  m_moving_right = true;
}

void UpdatePhysics(World& _world) {
  if (_world.m_moving_right) {
    _world.m_position.x += 10.0f;
    _world.m_position.y += 10.0f;
  } else {
    _world.m_position.x -= 10.0f;
    _world.m_position.y -= 10.0f;
  }

  if (_world.m_position.x < 0.0f || _world.m_position.y < 0.0f) {
    _world.m_moving_right = true;
  } else if (_world.m_position.x > 800.0f || _world.m_position.y > 800.0f) {
    _world.m_moving_right = false;
  }
}