#include <tuple>
#include <array>
#include <iostream>
#include <vector>

struct foo {
  std::vector<int> vec;

  foo operator,(int i) {
    vec.push_back(i);
    return *this;
  }
};

int main() {

  auto f = (foo(), 54, 4, 8, 12, 5, 8).vec;

  for (auto i : f)
    std::cout << i << ", ";

  return 0;
}
