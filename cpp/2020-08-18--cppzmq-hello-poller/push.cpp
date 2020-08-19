
#define ZMQ_BUILD_DRAFT_API
#include <winsock.h>
#include <zmq.hpp>
#include <iostream>

int main() {
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::pair);
  sock.bind("tcp://127.0.0.1:5678");

  std::cout << "setting up the poller\n";

  zmq::poller_t<> out_poller;
  out_poller.add(sock, zmq::event_flags::pollout);
  std::vector<zmq::poller_event<>> out_events(1);

  const std::chrono::milliseconds timeout{ 400 };

  std::cout << "give message to send: ";
  std::string message;
  std::getline(std::cin, message);
  auto buff = zmq::buffer(message);

  std::cout << "sending...\n";

  const auto nout = out_poller.wait_all(out_events, timeout);
  if (!nout) {
    std::cout << "timeout...\n";
  } else {
    auto sres = out_events[0].socket.send(buff, zmq::send_flags::none);
    std::cout << "sent the message\n";
  }

  std::cout << "done\n";
}