
#include "graphics.hpp"
#include "physics.hpp"

Window::Window(decltype(updatable.update_on_target) _update_on_target)
  : updatable(_update_on_target) {}

void UpdateGraphics(const World& _world, Window& _window) {}
