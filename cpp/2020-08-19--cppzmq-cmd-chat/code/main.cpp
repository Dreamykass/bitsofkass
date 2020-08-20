
#include <iostream>
#include <string>

#include <fmt/format.h>

int main() {
  std::cout << "hello\n";

  while (true) {
    std::cout << "--------------------------\n";
    std::cout << "your input: ";
    std::string input;
    std::getline(std::cin, input);

    auto pos = input.find_first_of(',');
    auto command = input.substr(pos + 1);
    auto argument = input.substr(0, pos);

    std::cout << "your command: " << command << "\n";
    if (command == "set") {
      std::cout << "setting port to " << argument << "\n";
    } else if (command == "add") {

    } else if (command == "rem") {

    } else if (command == "read") {

    } else if (command == "send") {

    } else {
      std::cout << "unknown command";
    }
  }

  std::cout << "bye\n";
  return 0;
}