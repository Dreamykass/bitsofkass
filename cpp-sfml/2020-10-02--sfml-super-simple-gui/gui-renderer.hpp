#pragma once

#include <cassert>
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <filesystem>

#include "label.hpp"
#include "button.hpp"
#include "gui-element.hpp"

// no cache
struct GuiRenderer {
private:
  std::map<std::string, std::unique_ptr<sf::Font>> m_fonts;
  sf::Text m_text;

public:
  void Render(sf::RenderWindow& _window, const GuiElement& _element) {
    auto element_ptr = &_element;
    auto label_ptr = dynamic_cast<const Label*>(element_ptr);
    auto button_ptr = dynamic_cast<const Button*>(element_ptr);

    if (label_ptr)
      RenderLabel(_window, *label_ptr);
    if (button_ptr)
      RenderButton(_window, *button_ptr);
  }

private:
  void RenderLabel(sf::RenderWindow& _window, const Label& _label) {

    if (m_fonts.count(_label.m_font) == 0) {
      auto f = std::make_unique<sf::Font>();
      std::string current_path = std::filesystem::current_path().string();
      auto path_to_font = current_path + "/../../" + _label.m_font;

      if (!std::filesystem::exists(path_to_font)) {
        std::cout << "!exists: " << path_to_font << "\n";
        std::cout << "current: " << std::filesystem::current_path() << "\n";
        assert(false);
      }
      assert(f->loadFromFile(path_to_font));

      m_fonts.emplace(_label.m_font, std::move(f));
    }

    m_text.setFont(*m_fonts[_label.m_font]);
    m_text.setPosition(_label.m_position);
    m_text.setString(_label.m_text);
    m_text.setColor(sf::Color::Black);
    // m_text.setCharacterSize(14);

    _window.draw(m_text);
  }

  void RenderButton(sf::RenderWindow&, const Button&) {}
};
