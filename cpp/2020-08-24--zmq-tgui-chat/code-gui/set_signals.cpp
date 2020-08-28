
#include "chat_gui.hpp"
#include "event_internal.hpp"

#include <fmt/format.h>
#include <spdlog/spdlog.h>

//   tgui::ChatBox::Ptr wg_chatbox_msg;
//   tgui::ListBox::Ptr wg_listbox_peers;

//   tgui::Button::Ptr wg_button_peer_add;
//   tgui::Button::Ptr wg_button_peer_rem;
//   tgui::Button::Ptr wg_button_ping;

//   tgui::EditBox::Ptr wg_editbox_name;
//   tgui::EditBox::Ptr wg_editbox_msg_in;
//   tgui::EditBox::Ptr wg_editbox_ip;
//   tgui::EditBox::Ptr wg_editbox_port;
//   tgui::EditBox::Ptr wg_editbox_peer;

void ChatGui::SetSignals() {

  wg_button_peer_add->connect("Pressed", [&]() {
    SPDLOG_INFO("wg_button_peer_add Pressed");

    auto peer = wg_editbox_peer->getText().toAnsiString();
    SPDLOG_INFO("peer for addition: {}", peer);

    wg_listbox_peers->addItem(peer);
    shared_data.events_for_incoming.enqueue(evi::PeerAddition(peer));
    shared_data.events_for_outgoing.enqueue(evi::PeerAddition(peer));
  });

  wg_button_peer_rem->connect("Pressed", [&]() {
    SPDLOG_INFO("wg_button_peer_rem Pressed");

    auto peer = wg_editbox_peer->getText().toAnsiString();
    SPDLOG_INFO("peer for removal: {}", peer);

    wg_listbox_peers->removeItem(peer);
    shared_data.events_for_incoming.enqueue(evi::PeerRemoval(peer));
    shared_data.events_for_outgoing.enqueue(evi::PeerRemoval(peer));
  });

  wg_button_ping->connect("Pressed", [&]() {
    SPDLOG_INFO("wg_button_ping Pressed");
    shared_data.events_for_gui.enqueue(
      evi::SystemString("sending out a ping..."));
  });

  wg_button_peer_add->connect("Pressed", [&]() {
    SPDLOG_INFO("wg_button_peer_add Pressed");

    auto new_peer = wg_editbox_peer->getText().toAnsiString();
    SPDLOG_INFO("new_peer == {}", new_peer);
  });

  wg_editbox_msg_in->connect("ReturnKeyPressed", [&]() {
    SPDLOG_INFO("wg_editbox_msg_in ReturnKeyPressed");

    auto message = wg_editbox_msg_in->getText().toAnsiString();
    shared_data.events_for_outgoing.enqueue(evi::Packet(evp::Message(message)));
    wg_chatbox_msg->addLine(
      fmt::format("{} (you): {}", shared_data.own_name.Load(), message));
  });
}
