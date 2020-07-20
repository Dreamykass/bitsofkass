
#include <rang.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include <toml++/toml.h>
using namespace std::string_view_literals;

#include <cxxopts.hpp>

#include "scope_exit.hpp"

int main(int argc, char** argv) {

  std::cout << rang::fg::yellow;
  MyScopeExit my_scope_exit([]() { std::cout << rang::fg::reset; });

  toml::table toml_table;
  std::string path = "";

  {
    cxxopts::Options options("example toml parser thing", "description?");

    options.add_options()(
      "p,path", "path to file to parse", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);

    try {
      path = result["path"].as<std::string>();

    } catch (...) {
      std::cerr << "\ncould not parse the arguments...";
      return 1;
    }
  }

  try {
    toml_table = toml::parse_file(path);

  } catch (const toml::parse_error& err) {
    std::cerr << "Error parsing file '" << *err.source().path << "':\n"
              << err.description() << "\n  (" << err.source().begin << ")\n";
    return 1;
  }

  {
    auto title = toml_table["title"];
    std::cout << "\ntitle and type: " << title << " (" << title.type() << ")";
    auto title_str = title.as<std::string>();
    std::cout << "\ntitle as string: " << *title_str;

    std::cout << "\nowner.name: " << toml_table["owner"]["name"];

    std::cout << "\nhosts.current: " << toml_table["hosts"]["current"];

    auto others = toml_table["hosts"]["others"].as_array();
    for (const auto& other : *others) {
      static int i = 0;
      i++;
      std::cout << "\n other " << i << ": " << *other.as_string();
    }
  }

  return 0;
}