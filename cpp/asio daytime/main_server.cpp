
#include <iostream>
#include <string>
#include <ctime>
#include "pretty_printer.hpp"

#pragma warning(disable : 4619)
#include <asio.hpp>

std::string make_daytime_string() {
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return "\n" + std::string(ctime(&now));
}

int main() {
  at_scope_exit atexit([]() { pretty_print("", "\nclient end..."); });
  pretty_print("y", "\nserver start!");

  try {
    asio::io_context io_context;

    asio::ip::tcp::acceptor acceptor(
      io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13));

    for (;;) {
      pretty_print("y", "\ncreating a socket and waiting for accept...");
      asio::ip::tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::string message = make_daytime_string();

      asio::error_code error;
      asio::write(socket, asio::buffer(message), error);
      pretty_print("y", "\nsent a message");

      if (!error) {
        pretty_print("r", "\ngot error: ");
        pretty_print("r", error.message());
      }
    }
  }

  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}