
#include "physics.hpp"

World::World(decltype(updatable.update_after_ms) _update_after_ms)
  : updatable(_update_after_ms) {}

void UpdatePhysics(World& _world) {}