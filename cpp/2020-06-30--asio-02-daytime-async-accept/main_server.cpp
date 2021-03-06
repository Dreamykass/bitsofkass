
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
}

int main() {
  at_scope_exit atexit([]() {
    pretty_print("y", "server end...");
    pretty_print("", "");
  });
  pretty_print("y", "server start!");

  try {
    pretty_print("y", "setting up context and running it");
    asio::io_context io_context;

    asio::ip::tcp::acceptor acceptor(
      io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 13));

    for (int i = 0; i < 3; i++) {
      pretty_print("g", "===========================================");
      pretty_print("y", "creating a socket and waiting for accept...");
      pretty_print("", "");
      // asio::ip::tcp::socket socket(io_context);
      // acceptor.accept(socket);

      auto handler = [](std::shared_ptr<asio::ip::tcp::socket> socket_ptr) {
        asio::ip::tcp::socket& socket = *socket_ptr;

        std::string message;
        std::array<char, 128> buf;
        asio::error_code error;

        {
          pretty_print("y", "reading from socket");
          size_t bytes_read = socket.read_some(asio::buffer(buf), error);
          pretty_print("y", "read from socket: ");
          pretty_print("b", std::string(buf.data(), bytes_read));
        }

        if (error) {
          pretty_print("r", "got error at read: ");
          pretty_print("r", "" + error.message());
        }

        pretty_print("y", "writing to socket: ");
        message = make_daytime_string();
        pretty_print("b", message);
        asio::write(socket, asio::buffer(message), error);
        pretty_print("y", "sent a message");

        if (error) {
          pretty_print("r", "got error at write: ");
          pretty_print("r", "" + error.message());
        }
      };

      std::shared_ptr<asio::ip::tcp::socket> socket_ptr;
      socket_ptr = std::make_shared<asio::ip::tcp::socket>(io_context);

      acceptor.async_accept(*socket_ptr, std::bind(handler, socket_ptr));
    }

    io_context.run();
    pretty_print("y", "ran the io_context");
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}