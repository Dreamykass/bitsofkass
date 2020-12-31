
#include <vector>
#include <iostream>

namespace elib_shared {
  __declspec(dllexport) void Print(const std::string& _in);

  __declspec(dllexport) std::vector<int> AddEachUp(
    const std::vector<std::vector<int>>& _vecs);

} // namespace testlib