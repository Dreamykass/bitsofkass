#pragma once

#include <SFML/Graphics.hpp>

#include "gui-element.hpp"

struct Label : public GuiElement {
  sf::Vector2f m_position;
  sf::String m_text;
  std::string m_font;
};
