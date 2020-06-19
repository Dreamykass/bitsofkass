
#include <iostream>
#include <rang.hpp>
#include <string>
#include <tbb/concurrent_queue.h>
#include <future>
#include <chrono>

#include <cli/cli.h>
#include <cli/clifilesession.h>

int main() {

  tbb::concurrent_bounded_queue<int> queue;
  std::cout << rang::fg::red << queue.capacity() << rang::style::reset << "\n";

  cli::SetColor();

  auto rootMenu = std::make_unique<cli::Menu>("cli");
  // cli::Cli cli(std::move(rootMenu));
  cli::Cli cli(std::make_unique<cli::Menu>("..."));
  auto& r = cli.RootMenuRef();
  // r = std::move(rootMenu);

  rootMenu->Insert(
    "hello",
    [](std::ostream& out) { out << "Hello, world\n"; },
    "Print hello world");

  auto subMenu = std::make_unique<cli::Menu>("sub");
  {
    subMenu->Insert(
      "hello",
      [](std::ostream& out) { out << "Hello, submenu world\n"; },
      "Print hello world in the submenu");
    subMenu->Insert(
      "demo",
      [](std::ostream& out) { out << "This is a sample!\n"; },
      "Print a demo string");
  }

  rootMenu->Insert(
    "rename", [&](std::ostream& out) { out << "Renaming..."; }, "Rename cli");

  rootMenu->Insert(
    "add",
    [&](std::ostream& out, int a, int b) {
      out << "a + b == " << a + b << "\n";
    },
    "Add a + b");

  rootMenu->Insert(
    "sub",
    [&](std::ostream& out) {
      out << "a + b == "
          << "\n";
    },
    "change to sub");

  cli.ExitAction(
    [](auto& out) { out << "Goodbye and thanks for all the fish.\n"; });

  cli::CliFileSession input(cli);

  input.Start();

  return 0;
}
