#include <zmq.hpp>
#include <iostream>

int main() {
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::pair);
  sock.connect("tcp://127.0.0.1:5678");

  std::cout << "receiving...\n";

  zmq::message_t mess;
  sock.recv(mess, zmq::recv_flags::none);

  std::cout << "received: " << mess.to_string() << "\n";
}