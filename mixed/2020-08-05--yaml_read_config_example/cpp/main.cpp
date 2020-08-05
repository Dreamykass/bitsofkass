
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

int main() {

  std::cout << "Hello from C++\n";

  auto config = YAML::LoadFile("../config.yaml");

  auto path_to_thing = config["PathToThing"].as<std::string>();
  std::cout << "path to thing: " << path_to_thing << "\n";

  auto error_codes = config["ErrorCodes"].as<std::map<int, std::string>>();
  std::cout << "error codes:\n";
  for (auto& code : error_codes)
    std::cout << " - " << code.first << ": " << code.second << "\n";

  return 0;
}
