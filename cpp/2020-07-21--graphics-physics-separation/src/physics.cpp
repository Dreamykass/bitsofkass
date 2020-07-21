
#include "physics.hpp"

World::World(decltype(updatable.update_on_target) _update_on_target)
  : updatable(_update_on_target) {}

void UpdatePhysics(World& _world) {}