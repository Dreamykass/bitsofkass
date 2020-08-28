
#include "chat_gui.hpp"

void ChatGui::Render() {
  window.clear(sf::Color::White);
  gui.draw();
  window.display();
}