
#define ZMQ_BUILD_DRAFT_API
#include <winsock.h>
#include <zmq.hpp>
#include <iostream>

int main() {
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::pair);
  sock.connect("tcp://127.0.0.1:5678");

  std::cout << "setting up the poller\n";

  zmq::poller_t<> in_poller;
  in_poller.add(sock, zmq::event_flags::pollin);
  std::vector<zmq::poller_event<>> in_events(1);

  const std::chrono::milliseconds timeout{ 400 };
  zmq::message_t mess;

  std::cout << "receiving...\n";

  // sock.recv(mess, zmq::recv_flags::none);

  for (int t = 0; t < 20; t++) {
    const auto nout = in_poller.wait_all(in_events, timeout);
    if (!nout) {
      std::cout << "timeout...\n";
    } else {
      auto sres = in_events[0].socket.recv(mess, zmq::recv_flags::none);
      std::cout << "received a message: " << mess.to_string() << "\n";
      t = 0;
    }
  }

  std::cout << "done\n";
}