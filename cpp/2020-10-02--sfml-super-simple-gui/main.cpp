
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cassert>
#include <iostream>
#include <filesystem>

#include "gui-renderer.hpp"
#include "gui-element.hpp"
#include "button.hpp"
#include "label.hpp"

int main() {
  GuiRenderer renderer;
  std::vector<std::unique_ptr<GuiElement>> gui_elements;

  // create elements
  {
    auto l1 = std::make_unique<Label>();
    l1->m_font = "Sansita_Swashed/SansitaSwashed-Regular.ttf";
    l1->m_position = { 100.f, 100.f };
    l1->m_text = "this is the first label with font sansita-swashed";
    gui_elements.emplace_back(std::move(l1));

    auto l2 = std::make_unique<Label>();
    l2->m_font = "Bangers/Bangers-Regular.ttf";
    l2->m_position = { 150.f, 150.f };
    l2->m_text = "this is the second label with font bangers";
    gui_elements.emplace_back(std::move(l2));
  }

  sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
  window.setFramerateLimit(60);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::White);

    for (const auto& element_ptr : gui_elements) {
      assert(element_ptr);
      renderer.Render(window, *element_ptr);
    }

    window.display();
  }

  return 0;

  return 0;
}