#include <zmq.hpp>
#include <zmq_addon.hpp>
#include <iostream>

int main() {
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::pair);
  sock.bind("tcp://127.0.0.1:5678");

  std::cout << "sending...\n";

  auto buff = zmq::str_buffer("Hello, world");
  auto result = sock.send(buff, zmq::send_flags::none);

  if (result.has_value())
    std::cout << "sent\n";
  else
    std::cout << "did not send\n";

  return 0;
}