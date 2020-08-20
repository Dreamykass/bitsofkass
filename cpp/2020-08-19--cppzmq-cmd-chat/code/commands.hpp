#pragma once

#include "networker.hpp"
#include "misc.hpp"

// fmt::print("possible commands: setport, addpeer, "
//            "rempeer, readmess, sendmess\n");

namespace cmmd {
  void setport(networker_t& netw, const std::string& arg) {
    fmt::print("setting port to {}\n", arg);
    try {
      auto port = std::stoi(arg);
      netw.setport(port);
    } catch (...) {
      fmt::print("invalid port given\n");
    };
  }
  void showaddr(networker_t& netw, const std::string&) {
    auto address = netw.getaddr();
    fmt::print("your address: {}", address);
  }

  void addpeer(networker_t& netw, const std::string& arg) {
    if (arg.find(':') != std::string::npos) {
      fmt::print("adding peer: {}\n", arg);
      netw.addpeer(arg);
    } else {
      auto [prot, rest] = split_string_by(netw.getaddr(), ':');
      auto [addr, _] = split_string_by(rest, ':');
      fmt::print("adding peer: {}\n", fmt::format("{}:{}:{}", prot, addr, arg));
      netw.addpeer(addr + ":" + arg);
    }
  }
  void rempeer(networker_t& netw, const std::string& arg) {
    if (arg.find(':') != std::string::npos) {
      fmt::print("removing peer: {}\n", arg);
      netw.rempeer(arg);
    } else {
      auto [prot, rest] = split_string_by(netw.getaddr(), ':');
      auto [addr, _] = split_string_by(rest, ':');
      fmt::print("adding peer: {}\n", fmt::format("{}:{}:{}", prot, addr, arg));
      netw.rempeer(addr + ":" + arg);
    }
  }

  void readmess(networker_t& netw, const std::string&) {
    auto messages = netw.readmess();

    fmt::print("messages, newest first:\n");
    for (const auto& m : messages)
      fmt::print(" - {}\n", m);
    fmt::print("done\n");
  }
  void sendmess(networker_t& netw, const std::string& arg) {
    fmt::print("sending message: {}", arg);
    netw.sendmess(netw.getaddr() + " says " + arg);
  }

}
