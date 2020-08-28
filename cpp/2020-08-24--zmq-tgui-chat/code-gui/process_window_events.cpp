
#include "chat_gui.hpp"

void ChatGui::ProcessWindowEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {

    if (event.type == sf::Event::Closed) {
      SPDLOG_INFO("event.type == sf::Event::Closed");
      window.close();
      shared_data.app_should_close.store(true);
      shared_data.events_for_outgoing.enqueue(std::monostate());
    }

    gui.handleEvent(event);
  }
}