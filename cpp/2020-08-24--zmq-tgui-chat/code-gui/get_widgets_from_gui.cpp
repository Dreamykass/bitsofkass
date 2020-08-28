
#include "chat_gui.hpp"

void ChatGui::GetWidgetsFromGui() {
  wg_chatbox_msg = gui.get<tgui::ChatBox>("ChatBoxMessages");
  wg_listbox_peers = gui.get<tgui::ListBox>("ListBoxPeers");

  wg_button_peer_add = gui.get<tgui::Button>("ButtonPeerAdd");
  wg_button_peer_rem = gui.get<tgui::Button>("ButtonPeerRemove");
  wg_button_ping = gui.get<tgui::Button>("ButtonPing");

  wg_editbox_name = gui.get<tgui::EditBox>("EditBoxName");
  wg_editbox_msg_in = gui.get<tgui::EditBox>("EditBoxMessageInput");
  wg_editbox_ip = gui.get<tgui::EditBox>("EditBoxIP");
  wg_editbox_port = gui.get<tgui::EditBox>("EditBoxPort");
  wg_editbox_peer = gui.get<tgui::EditBox>("EditBoxPeer");
}