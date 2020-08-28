
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <future>

#include "shared_data.hpp"
#include "chat_gui.hpp"
#include "work_incoming.hpp"
#include "work_outgoing.hpp"

int main() {
  // spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] -- %v");
  spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [%22!s:%3#] -- %v");

  SPDLOG_INFO("hello");

  SharedData shared_data;
  ChatGui chat_gui(shared_data);

  auto incoming_worker = std::async(incoming_work, std::ref(shared_data));
  auto outgoing_worker = std::async(outgoing_work, std::ref(shared_data));

  while (shared_data.app_should_close.load() == false) {
    chat_gui.ProcessWindowEvents();
    chat_gui.ProcessInternalEvents();
    chat_gui.Render();
  }

  incoming_worker.get();
  outgoing_worker.get();

  SPDLOG_INFO("bye");
  return 0;
}
