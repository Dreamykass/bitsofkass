
#include <iostream>
#include <string>
#include <map>
#include <functional>

#include <fmt/format.h>

#include "networker.hpp"
#include "commands.hpp"
#include "misc.hpp"

int main() {
  fmt::print("hello\n");

  networker_t networker;

  std::map<std::string, std::function<void(networker_t&, const std::string&)>>
    commands_map;
  commands_map["addpeer"] = cmmd::addpeer;
  commands_map["add"] = cmmd::addpeer;
  commands_map["readmess"] = cmmd::readmess;
  commands_map["read"] = cmmd::readmess;
  commands_map["rempeer"] = cmmd::rempeer;
  commands_map["rem"] = cmmd::rempeer;
  commands_map["sendmess"] = cmmd::sendmess;
  commands_map["send"] = cmmd::sendmess;
  commands_map["setport"] = cmmd::setport;
  commands_map["set"] = cmmd::setport;
  commands_map["showaddr"] = cmmd::showaddr;
  commands_map["show"] = cmmd::showaddr;
  commands_map["listpeers"] = cmmd::listpeers;
  commands_map["list"] = cmmd::listpeers;

  while (true) {
    fmt::print("\n--------------------------\n");
    fmt::print("your input: ");
    std::string input;
    std::getline(std::cin, input);

    auto [command, argument] = split_string_by(input, ' ');

    fmt::print("your command: {}\n", command);

    if (command == "exit") {
      break;

    } else if (commands_map.contains(command)) {
      commands_map[command](networker, argument);

    } else {
      fmt::print("unknown command given\npossible commands_map: ");
      for (auto [c, _] : commands_map)
        fmt::print("{}, ", c);
    }
  }

  fmt::print("bye\n");
  return 0;
}
