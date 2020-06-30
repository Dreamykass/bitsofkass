
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "pretty_printer.hpp"

#pragma warning(disable : 4619)
#include <asio.hpp>

std::string make_daytime_string() {
  std::time_t now =
    std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  std::string s(30, '\0');
  std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
  return s;

  // std::string str;
  // str = "current server time: ";
  // str += std::to_string(std::chrono::system_clock::now());
  // return str;
}

int main() {
  at_scope_exit atexit([]() {
    pretty_print("y", "\nserver end...");
    pretty_print("", "");
  });
  pretty_print("y", "\nserver start!");

  try {
    asio::io_context io_context;

    asio::ip::tcp::acceptor acceptor(
      io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13));

    for (;;) {
      pretty_print("g", "\n===========================================");
      pretty_print("y", "\ncreating a socket and waiting for accept...");
      asio::ip::tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::string message;
      std::array<char, 128> buf;
      asio::error_code error;

      {
        pretty_print("y", "\nreading from socket");
        size_t bytes_read = socket.read_some(asio::buffer(buf), error);
        pretty_print("y", "\nread from socket: ");
        pretty_print("b", std::string(buf.data(), bytes_read));
      }

      if (error) {
        pretty_print("r", "\ngot error at read: ");
        pretty_print("r", "\n" + error.message());
      }

      pretty_print("y", "\nwriting to socket: ");
      message = make_daytime_string();
      pretty_print("b", message);
      asio::write(socket, asio::buffer(message), error);
      pretty_print("y", "\nsent a message");

      if (error) {
        pretty_print("r", "\ngot error at write: ");
        pretty_print("r", "\n" + error.message());
      }

      socket.close();
    }
  }

  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}