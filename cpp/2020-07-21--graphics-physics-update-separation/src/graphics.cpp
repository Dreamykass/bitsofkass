
#include "graphics.hpp"
#include "physics.hpp"

#include <SFML/Graphics.hpp>

Window::Window(decltype(m_updatable.update_after_ms) _update_after_ms)
  : m_updatable(_update_after_ms) {

  m_window.create(sf::VideoMode(800, 800), "SFML works!");
}

void UpdateGraphics(const World& _world, Window& _window, bool& _open) {

  sf::Event event;
  while (_window.m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      _open = false;
  }

  _window.m_window.clear();

  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(_world.m_position.x, _world.m_position.y);
  _window.m_window.draw(shape);

  _window.m_window.display();
}
