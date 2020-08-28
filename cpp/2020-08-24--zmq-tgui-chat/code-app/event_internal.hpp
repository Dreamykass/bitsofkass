#pragma once

#include <variant>
#include <string>

#include "event_packet.hpp"

namespace evi {
  struct SystemString {
    std::string str;
    SystemString(std::string _str)
      : str(_str){};
  };

  struct PeerAddition {
    std::string addr;
    PeerAddition(std::string _addr)
      : addr(_addr){};
  };
  struct PeerRemoval {
    std::string addr;
    PeerRemoval(std::string _addr)
      : addr(_addr){};
  };

  struct Packet {
    evp::EventPacket packet;
    Packet(evp::EventPacket _p)
      : packet(_p){};
  };

  //
  using EventInternal = std::
    variant<std::monostate, SystemString, PeerAddition, PeerRemoval, Packet>;
}