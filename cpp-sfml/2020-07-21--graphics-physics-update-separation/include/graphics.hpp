#pragma once

#include <chrono>
#include "common.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

struct Window {
  Updatable m_updatable;
  sf::RenderWindow m_window;

  Window(decltype(m_updatable.update_after_ms) _update_after_ms);
};

struct World;

void UpdateGraphics(const World& _world, Window& _window, bool& _open);
