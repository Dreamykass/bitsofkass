#pragma once

#include <string>
#include <tuple>

std::pair<std::string, std::string> split_string_by(std::string input, char s) {
  auto pos = input.find_first_of(s);
  return std::make_pair(input.substr(0, pos), input.substr(pos + 1));
}