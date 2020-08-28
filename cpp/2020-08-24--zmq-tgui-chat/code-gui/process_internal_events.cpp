
#include <spdlog/spdlog.h>
#include <fmt/format.h>

#include "chat_gui.hpp"
#include "make_visitor.hpp"
#include "event_internal.hpp"

void ChatGui::ProcessInternalEvents() {

  auto visitor = stx::make_visitor(
    [&](const evi::SystemString& ss) {
      SPDLOG_INFO("const evi::SystemString&.str: {}", ss.str);
      wg_chatbox_msg->addLine(fmt::format("system: {}", ss.str),
                              tgui::Color::Red);
    },

    // ignored:
    [&](const std::monostate&) {},
    [&](const evi::PeerAddition&) {},
    [&](const evi::PeerRemoval&) {},
    [&](const evi::Packet&) {});
  // end of make_visitor

  evi::EventInternal event;
  while (shared_data.events_for_gui.try_dequeue(event)) {
    std::visit(visitor, event);
  }
}