
#include "ilib.hpp"

std::vector<std::vector<int>> ilib::CreateVectors() {
  std::vector<std::vector<int>> out;
  std::srand(42);

  for (int i = 0; i < 10; i++) {
    std::vector<int> i_vec;
    for (int j = 0; j < 24; j++) {
      i_vec.push_back(std::rand() % 100);
    }
    out.push_back(i_vec);
  }

  return out;
}