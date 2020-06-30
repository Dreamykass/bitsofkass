
#include <iostream>
#include <array>
#include "pretty_printer.hpp"

#pragma warning(disable : 4619)
#include <asio.hpp>

int main() {
  at_scope_exit atexit([]() {
    pretty_print("y", "\nclient end...");
    pretty_print("", "");
  });
  pretty_print("y", "\nclient start!");

  try {
    asio::io_context io_context;
    pretty_print("y", "\ncreated a context");

    asio::ip::tcp::resolver resolver(io_context);

    asio::ip::tcp::resolver::results_type endpoints =
      resolver.resolve("localhost", "daytime");
    pretty_print("y", "\nresolved");

    asio::ip::tcp::socket socket(io_context);
    pretty_print("y", "\ncreated a socket with the context");

    asio::connect(socket, endpoints);
    pretty_print("y", "\nconnected");

    std::string message;
    std::array<char, 128> buf;
    asio::error_code error;

    message = "hello";
    pretty_print("y", "\nwriting to socket: ");
    pretty_print("b", message);
    asio::write(socket, asio::buffer(message), error);

    for (;;) {
      size_t len = socket.read_some(asio::buffer(buf), error);

      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw asio::system_error(error); // Some other error.

      // std::cout.write(buf.data(), len);
      pretty_print("y", "\nread from socket: ");
      pretty_print("b", "" + std::string(buf.data(), len));
    }

    pretty_print("y", "\nnicely exiting the try block");

  } catch (std::exception& e) {
    pretty_print("r", "\ngot exception: " + std::string(e.what()));
  }

  return 0;
}