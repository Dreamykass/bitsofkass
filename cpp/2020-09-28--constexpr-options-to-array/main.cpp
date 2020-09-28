#include <tuple>
#include <array>
#include <iostream>

constexpr bool foo = false;

constexpr auto foo_if_true() -> auto {
  return std::make_tuple("a", "b", "c", "d", "e", "f");
}

constexpr auto foo_if_false() -> auto {
  return std::make_tuple("x", "y", "z");
}

constexpr auto foo_f() -> auto {
  if constexpr (foo == true)
    return foo_if_true();
  else
    return foo_if_false();
}

template<typename tuple_t>
constexpr auto get_array_from_tuple(tuple_t&& tuple) {
  constexpr auto get_array = [](auto&&... x) {
    return std::array{ std::forward<decltype(x)>(x)... };
  };
  return std::apply(get_array, std::forward<tuple_t>(tuple));
}

int main() {
  auto arr = get_array_from_tuple(foo_f());

  std::cout << "size of arr: " << arr.size() << ", contents:\n";
  for (auto i : arr)
    std::cout << i << "\n";

  return 0;
}