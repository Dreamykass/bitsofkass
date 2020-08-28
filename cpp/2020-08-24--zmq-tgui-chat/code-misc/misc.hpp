#pragma once

#include <string>
#include <tuple>
#include <utility>
#include <mutex>

inline std::pair<std::string, std::string> SplitStringBy(std::string in,
                                                         char s) {
  auto pos = in.find_first_of(s);
  return std::make_pair(in.substr(0, pos), in.substr(pos + 1));
}

class SafeString {
private:
  std::mutex mut;
  std::string str;

public:
  void Store(std::string _str) {
    auto _ = std::unique_lock(mut);
    str = _str;
  }

  std::string Load() {
    auto _ = std::unique_lock(mut);
    return str;
  }
};
