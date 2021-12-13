#include <tuple>
#include <array>
#include <iostream>
#include <vector>
#include "cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/array.hpp"
#include <sstream>
#include <ostream>
#include <cassert>
#include <fstream>

struct TrainingPointsTemp {
  int version = 0;
  std::vector<int8_t> oxygenation = {};
  std::vector<int8_t> acid = {};
  std::vector<std::array<float, 4>> lockin = {};

  template<class Archive>
  void serialize(Archive& ar) {
    ar(version, oxygenation, acid, lockin);
  }
};

std::vector<char> ss_to_vec(std::stringstream& ss) {
  auto s = ss.str();
  return std::vector<char>(s.begin(), s.end());
}

std::stringstream vec_to_ss(std::vector<char> vec) {
  std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
  std::string s(vec.begin(), vec.end());
  ss << s;
  return ss;
}

int main() {
  try {

    {

      auto t1 = TrainingPointsTemp{};
      auto t2 = TrainingPointsTemp{};

      std::stringstream os_out(std::ios::binary | std::ios::out);
      cereal::BinaryOutputArchive archive_out(os_out);
      archive_out(t1);

      auto vec = ss_to_vec(os_out);
      std::cout << vec.size() << "\n";

      std::stringstream os_in = vec_to_ss(vec);
      cereal::BinaryInputArchive archive_in(os_in);
      archive_in(t2);

      assert(t1.acid.size() == t2.acid.size());
      assert(t1.oxygenation.size() == t2.oxygenation.size());
      assert(t1.lockin.size() == t2.lockin.size());
    }

    {
      auto t1 = TrainingPointsTemp{};
      t1.oxygenation = { 1, 2, 3 };
      t1.acid = { 0, 0, 5, 6, 7, 0 };
      t1.lockin = { { 0, 0, 0, 0 }, { 3, 4, 2, 1 }, { 8, 7, 6, 5 } };
      auto t2 = TrainingPointsTemp{};

      std::stringstream os_out(std::ios::binary | std::ios::out);
      cereal::BinaryOutputArchive archive_out(os_out);
      archive_out(t1);

      auto vec = ss_to_vec(os_out);
      std::cout << vec.size() << "\n";

      std::stringstream os_in = vec_to_ss(vec);
      cereal::BinaryInputArchive archive_in(os_in);
      archive_in(t2);

      assert(t1.acid.size() == t2.acid.size());
      assert(t1.oxygenation.size() == t2.oxygenation.size());
      assert(t1.lockin.size() == t2.lockin.size());

      for (size_t i = 0; i < t1.acid.size(); i++)
        assert(t1.acid[i] == t2.acid[i]);
      for (size_t i = 0; i < t1.oxygenation.size(); i++)
        assert(t1.oxygenation[i] == t2.oxygenation[i]);
      for (size_t i = 0; i < t1.lockin.size(); i++)
        assert(t1.lockin[i] == t2.lockin[i]);
    }

    std::cout << " ok \n";
  } catch (std::exception e) {
    std::cout << " exception \n";
    std::cout << e.what();
  }
  return 0;
}
