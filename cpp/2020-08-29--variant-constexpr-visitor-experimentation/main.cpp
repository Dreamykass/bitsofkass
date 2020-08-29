
#include <typeinfo>
#include <type_traits>
#include <variant>
#include <string>
#include <iostream>

// ---------------------------------------------------------------------------

struct Fruit {
  virtual std::string Color() const = 0;
};

struct Banana : public Fruit {
  std::string Color() const final { return "yellow"; };
};
struct Apple : public Fruit {
  std::string Color() const final { return "red"; };
};

// ---------------------------------------------------------------------------

void CheckColor1(std::monostate) {
  std::cout << "monostate\n";
}
void CheckColor1(const Fruit& _fruit) {
  std::cout << "color: " << _fruit.Color() << "\n";
}

// ---------------------------------------------------------------------------

template<typename V>
void CheckColor2(const V& v) {
  if constexpr (std::is_same<V, std::monostate>::value) {
    std::cout << "monostate\n";

  } else if (std::is_base_of<Fruit, V>::value) {
    const auto& f = static_cast<const Fruit&>(v);
    std::cout << "color: " << f.Color() << "\n";

  } else {
    // static_assert(false);
  };
}

// ---------------------------------------------------------------------------

int main() {
  std::variant<std::monostate, Banana, Apple> fruit = Banana();

  // CheckColor1
  {
    std::visit([](auto f) { CheckColor1(f); }, fruit);

    fruit = {};
    std::visit([](auto f) { CheckColor1(f); }, fruit);

    fruit = Banana();
    std::visit([](auto f) { CheckColor1(f); }, fruit);

    fruit = Apple();
    std::visit([](auto f) { CheckColor1(f); }, fruit);

    fruit = {};
    std::visit([](auto f) { CheckColor1(f); }, fruit);
  }
  // /CheckColor1

  std::cout << "-----------------------------------------------------------\n";

  // CheckColor2
  {
    fruit = Banana();
    std::visit([](auto f) { CheckColor2(f); }, fruit);

    fruit = {};
    std::visit([](auto f) { CheckColor2(f); }, fruit);

    fruit = Banana();
    std::visit([](auto f) { CheckColor2(f); }, fruit);

    fruit = Apple();
    std::visit([](auto f) { CheckColor2(f); }, fruit);

    fruit = {};
    std::visit([](auto f) { CheckColor2(f); }, fruit);
  }
  // /CheckColor2

  return 0;
}