#pragma once

#include <TGUI/TGUI.hpp>
#include <filesystem>

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
  tgui::Button::Ptr wg_button_ping;

  tgui::EditBox::Ptr wg_editbox_name;
  tgui::EditBox::Ptr wg_editbox_msg_in;
  tgui::EditBox::Ptr wg_editbox_ip;
  tgui::EditBox::Ptr wg_editbox_port;
  tgui::EditBox::Ptr wg_editbox_peer;

public:
  ChatGui(SharedData& _shared_data)
    : shared_data(_shared_data) {

    window.create({ 800, 600 }, "chat-gui");
    window.setFramerateLimit(60);

    std::string path_to_project;
    if (std::filesystem::exists(".clang-format"))
      path_to_project = "";
    else if (std::filesystem::exists("../../.clang-format"))
      path_to_project = "../../";
    else
      SPDLOG_CRITICAL("can't find project directory, current path: {}",
                      std::filesystem::current_path().string());

    gui.setTarget(window);
    gui.loadWidgetsFromFile(path_to_project + "resources/form.txt");

    GetWidgetsFromGui();
    SetSignals();
  }

  void ProcessWindowEvents();

  void ProcessInternalEvents();

  void Render();

private:
  void GetWidgetsFromGui();
  void SetSignals();
};
