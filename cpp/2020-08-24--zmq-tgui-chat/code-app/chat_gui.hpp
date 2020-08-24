#pragma once

#include <TGUI/TGUI.hpp>

#include "shared_data.hpp"

class ChatGui {
private:
  sf::RenderWindow window;
  tgui::Gui gui;
  SharedData& shared_data;

  tgui::ChatBox::Ptr wg_chatbox_msg;
  tgui::ListBox::Ptr wg_listbox_peers;

  tgui::Button::Ptr wg_button_peer_add;
  tgui::Button::Ptr wg_button_peer_rem;

  tgui::EditBox::Ptr wg_editbox_msg_in;
  tgui::EditBox::Ptr wg_editbox_ip;
  tgui::EditBox::Ptr wg_editbox_port;
  tgui::EditBox::Ptr wg_editbox_peer;

public:
  ChatGui(SharedData& _shared_data)
    : shared_data(_shared_data) {

    window.create({ 800, 600 }, "chat-gui");
    window.setFramerateLimit(60);

    gui.setTarget(window);
    gui.loadWidgetsFromFile("resources/form.txt");

    GetWidgetsFromGui();
  }

  void ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        shared_data.app_should_close.store(true);
        SPDLOG_INFO("event.type == sf::Event::Closed");
      }
      gui.handleEvent(event);
    }
  }

  void Render() {
    window.clear(sf::Color::White);
    gui.draw();
    window.display();
  }

private:
  void GetWidgetsFromGui() {
    wg_chatbox_msg = gui.get<tgui::ChatBox>("ChatBoxMessages");
    wg_listbox_peers = gui.get<tgui::ListBox>("ListBoxPeers");

    wg_button_peer_add = gui.get<tgui::Button>("ButtonPeerRemove");
    wg_button_peer_rem = gui.get<tgui::Button>("ButtonPeerAdd");

    wg_editbox_msg_in = gui.get<tgui::EditBox>("EditBoxMessageInput");
    wg_editbox_ip = gui.get<tgui::EditBox>("EditBoxIP");
    wg_editbox_port = gui.get<tgui::EditBox>("EditBoxPort");
    wg_editbox_peer = gui.get<tgui::EditBox>("EditBoxPeer");
  }
};
