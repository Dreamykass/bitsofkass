
#include <iostream>
#include <toml.h>

int main() {

  std::ifstream ifstream;
  ifstream.open("toml.toml");
  assert(ifstream.is_open());

  toml::ParseResult parse_result = toml::parse(ifstream);

  if (!parse_result.valid()) {
    std::cout << parse_result.errorReason;
    return 1;
  }

  auto& parse_value = parse_result.value;

  const auto title = parse_value.find("title");
  if (title && title->is<std::string>()) {
    std::cout << "\ntitle: " << title->as<std::string>();
  }

  std::cout << "\ntitle fast: " << parse_value.get<std::string>("title");

  std::cout << "\nowner name: " << parse_value.get<std::string>("owner.name");

  std::cout << "\ncurrent host: "
            << parse_value.get<std::string>("hosts.current");

  const auto hosts = parse_value.get<std::vector<std::string>>("hosts.others");
  for (const auto& host : hosts)
    std::cout << "\n -- " << host;

  return 0;
}