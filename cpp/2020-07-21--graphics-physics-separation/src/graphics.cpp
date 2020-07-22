
#include "graphics.hpp"
#include "physics.hpp"

Window::Window(decltype(updatable.update_after_ms) _update_after_ms)
  : updatable(_update_after_ms) {}

void UpdateGraphics(const World& _world, Window& _window) {}
