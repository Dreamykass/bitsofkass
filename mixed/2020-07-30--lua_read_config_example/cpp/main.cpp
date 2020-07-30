
#define SOL_ALL_SAFETIES_ON 1

#include "sol.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main() {

  std::cout << "Hello from C++\n";

  sol::state lua_state;

  std::ifstream script_file_stream("../script.lua");
  std::string script_str((std::istreambuf_iterator<char>(script_file_stream)),
                         (std::istreambuf_iterator<char>()));
  lua_state.script(script_str);

  auto ErrorCodes = lua_state["ErrorCodes"].get<sol::table>();
  std::cout << "Error code 007: " + ErrorCodes[7].get<std::string>() + "\n";
  std::cout << "Error code -1: " + ErrorCodes[-1].get_or<std::string>("nil") +
                 "\n";

  std::cout << "Error codes and their strings:\n";
  for (auto& [key, val] : ErrorCodes) {
    std::cout << "[" << key.as<int>() << ", " << val.as<std::string>() << "]\n";
  }

  return 0;
}
