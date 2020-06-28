
#include <iostream>
#include <array>
#include "pretty_printer.hpp"

#pragma warning(disable : 4619)
#include <asio.hpp>

int main(int argc, char* argv[]) {
  at_scope_exit atexit([]() { pretty_print("", "\nclient end..."); });
  pretty_print("y", "\nclient start!");

  try {
    // if (argc != 2) {
    //   std::cerr << "Usage: client <host>" << std::endl;
    //   return 1;
    // }

    asio::io_context io_context;
    pretty_print("y", "\ncreated a context");

    asio::ip::tcp::resolver resolver(io_context);

    // tcp::resolver::results_type endpoints =
    //   resolver.resolve(argv[1], "daytime");
    asio::ip::tcp::resolver::results_type endpoints =
      resolver.resolve("localhost", "daytime");
    pretty_print("y", "\nresolved");

    asio::ip::tcp::socket socket(io_context);
    pretty_print("y", "\ncreated a socket with the context");

    asio::connect(socket, endpoints);
    pretty_print("y", "\nconnected");

    for (;;) {
      std::array<char, 128> buf;
      asio::error_code error;

      size_t len = socket.read_some(asio::buffer(buf), error);

      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw asio::system_error(error); // Some other error.

      // std::cout.write(buf.data(), len);
      pretty_print("y", "\ngot message: ");
      pretty_print("y", std::string(buf.data(), len));
    }

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}