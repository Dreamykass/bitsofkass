
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <TGUI/TGUI.hpp>

#include "misc.hpp"

int main() {
  fmt::print("hello\n");

  sf::RenderWindow window{ { 800, 600 }, "Window" };
  tgui::Gui gui{ window }; // Create the gui and attach it to the window
  gui.loadWidgetsFromFile("resources/form.txt");

  gui.get<tgui::ChatBox>("ChatBoxMessages")->addLine("siema");
  for (int i = 0; i < 100; i++)
    gui.get<tgui::ChatBox>("ChatBoxMessages")->addLine("siema");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      gui.handleEvent(event); // Pass the event to the widgets
    }

    window.clear(sf::Color::White);
    gui.draw(); // Draw all widgets
    window.display();
  }

  fmt::print("bye\n");
  return 0;
}
