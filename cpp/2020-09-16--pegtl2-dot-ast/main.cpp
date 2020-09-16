#include <iostream>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>
#include <tao/pegtl/contrib/parse_tree_to_dot.hpp>

// This example uses the included JSON grammar
#include <tao/pegtl/contrib/json.hpp>

namespace pegtl = tao::pegtl;

using grammar = pegtl::must<pegtl::json::text, pegtl::eof>;

template<typename Rule>
using selector = pegtl::parse_tree::selector<
  Rule,
  pegtl::parse_tree::store_content::on<pegtl::json::null,
                                       pegtl::json::true_,
                                       pegtl::json::false_,
                                       pegtl::json::number,
                                       pegtl::json::string,
                                       pegtl::json::key,
                                       pegtl::json::array,
                                       pegtl::json::object,
                                       pegtl::json::member>>;

int main(int argc, char** argv) {
  try {
    if (argc != 2)
      return 1;

    pegtl::argv_input in(argv, 1);
    const auto root = pegtl::parse_tree::parse<grammar, selector>(in);
    if (root) {
      pegtl::parse_tree::print_dot(std::cout, *root);
    }
  } catch (const std::exception& e) {
    std::cout << "\n\ne.what(): " << e.what() << "\n";
  }
  return 0;
}