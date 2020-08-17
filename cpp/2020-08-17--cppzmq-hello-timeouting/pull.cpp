#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <errno.h>

int main() {
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::pair);
  sock.connect("tcp://127.0.0.1:5678");

  std::cout << "entering the timeout/receive loop...\n";

  zmq::message_t mess;
  size_t timeout = 0;
  while (timeout < 1000) {

    auto result = sock.recv(mess, zmq::recv_flags::dontwait);
    if (result.has_value()) {
      std::cout << "received: " << mess.to_string() << "\n";
      timeout = 0;
    }

    if (timeout % 100 == 0)
      std::cout << "waiting... time is : " << timeout << "/1000\n";

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2ms);
    timeout++;
  }

  std::cout << "timeout reached\n";

  return 0;
}