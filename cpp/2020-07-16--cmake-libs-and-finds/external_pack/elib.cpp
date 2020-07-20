
#include "elib.hpp"

void elib::Print(const std::string& _in) {
  std::cout << _in;
};

std::vector<int> elib::AddEachUp(const std::vector<std::vector<int>>& _vecs) {
  std::vector<int> out;

  for (const auto& vec : _vecs) {
    int sum = 0;

    for (const auto& i : vec) {
      sum += i;
    }

    out.push_back(sum);
  }

  return out;
}
