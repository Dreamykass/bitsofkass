
#include <rang.hpp>
#include <mutex>
#include <thread>

#include "pretty_printer.hpp"

void pretty_print(std::string _color, std::string _message) {
  static std::mutex mutex;
  std::unique_lock ulock(mutex);

  if (_color == "r")
    std::cout << rang::fg::red;
  else if (_color == "g")
    std::cout << rang::fg::green;
  else if (_color == "b")
    std::cout << rang::fg::blue;
  else if (_color == "y")
    std::cout << rang::fg::yellow;
  else
    std::cout << rang::fg::reset;

  std::cout << "\n";
  std::cout << "[" << std::this_thread::get_id() << "] ";
  std::cout << _message;
}