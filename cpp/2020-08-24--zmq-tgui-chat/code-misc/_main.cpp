
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <TGUI/TGUI.hpp>

#include "shared_data.hpp"
#include "chat_gui.hpp"

int main() {
  SPDLOG_INFO("main, hello");

  SharedData shared_data;
  ChatGui chat_gui(shared_data);

  while (shared_data.app_should_close.load() == false) {
    chat_gui.ProcessEvents();
    chat_gui.Render();
  }

  SPDLOG_INFO("main, bye");
  return 0;
}
