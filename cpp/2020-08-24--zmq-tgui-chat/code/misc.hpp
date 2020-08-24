#pragma once

#include <string>
#include <tuple>
#include <mutex>

std::pair<std::string, std::string> split_string_by(std::string input, char s) {
  auto pos = input.find_first_of(s);
  return std::make_pair(input.substr(0, pos), input.substr(pos + 1));
}

class safe_string {
private:
  std::mutex mut;
  std::string str;

public:
  void store(std::string _str) {
    auto _ = std::unique_lock(mut);
    str = _str;
  }

  std::string load() {
    auto _ = std::unique_lock(mut);
    return str;
  }
};
