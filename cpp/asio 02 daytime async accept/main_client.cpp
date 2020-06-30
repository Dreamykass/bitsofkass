
#include <iostream>
#include <array>
#include "pretty_printer.hpp"

#pragma warning(disable : 4619)
#include <asio.hpp>

int main() {
  at_scope_exit atexit([]() {
    pretty_print("y", "client end...");
    pretty_print("", "");
  });
  pretty_print("y", "client start!");

  try {
    asio::io_context io_context;
    pretty_print("y", "created a context");

    asio::ip::tcp::resolver resolver(io_context);

    asio::ip::tcp::resolver::results_type endpoints =
      resolver.resolve("localhost", "daytime");
    pretty_print("y", "resolved");

    asio::ip::tcp::socket socket(io_context);
    pretty_print("y", "created a socket with the context");

    asio::connect(socket, endpoints);
    pretty_print("y", "connected");

    std::string message;
    std::array<char, 128> buf;
    asio::error_code error;

    message = "hello";
    pretty_print("y", "writing to socket: ");
    pretty_print("b", message);
    asio::write(socket, asio::buffer(message), error);

    for (;;) {
      size_t len = socket.read_some(asio::buffer(buf), error);

      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw asio::system_error(error); // Some other error.

      // std::cout.write(buf.data(), len);
      pretty_print("y", "read from socket: ");
      pretty_print("b", "" + std::string(buf.data(), len));
    }

    pretty_print("y", "nicely exiting the try block");

  } catch (std::exception& e) {
    pretty_print("r", "got exception: " + std::string(e.what()));
  }

  return 0;
}