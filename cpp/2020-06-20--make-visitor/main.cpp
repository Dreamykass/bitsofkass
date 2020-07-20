
#include <iostream>
#include <rang.hpp>

#include <variant>

#include "make_visitor.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("make_visitor") {
  std::vector<std::string> strings;

  auto visitor = make_visitor(
    [&](int i) { strings.push_back("int " + std::to_string(i)); },
    [&](float f) { strings.push_back("float " + std::to_string((int)(f))); },
    [&](bool b) { strings.push_back("bool " + std::to_string(b)); });

  std::variant<int, float, bool> variant;

  variant = 2;
  std::visit(visitor, variant);

  variant = 33.0f;
  std::visit(visitor, variant);

  variant = true;
  std::visit(visitor, variant);

  CHECK(strings[0] == "int 2");
  CHECK(strings[1] == "float 33");
  CHECK(strings[2] == "bool 1");
}
