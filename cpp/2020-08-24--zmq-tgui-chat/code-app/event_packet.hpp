#pragma once

#include <variant>

namespace evp {
  struct Message {
    std::string str;
    Message(std::string _str)
      : str(_str){};
  };

  struct Ping {};

  struct PingBack {};

  //
  using EventPacket = std::variant<Message, Ping, PingBack>;
}
