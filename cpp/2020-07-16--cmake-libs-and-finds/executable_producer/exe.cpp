
#include <iostream>
#include "ilib.hpp"
#include "elib.hpp"

int main() {
  std::cout << "---\nhello\n";

  auto vecs = ilib::CreateVectors();

  std::cout << "first element of first vec: " << vecs[0][0] << "\n";

  auto vecs_sums = elib::AddEachUp(vecs);

  std::cout << "sum of first vec: " << vecs_sums[0] << "\n";

  std::cout << "hello\n---\n";
  return 0;
}