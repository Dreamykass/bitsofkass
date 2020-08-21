
#include "networker.hpp"
#include <map>
#include <zmq.hpp>

namespace {
  const std::chrono::milliseconds timeout{ 200 };
}

void networker_t::incoming_work() {
  zmq::context_t context;
  zmq::poller_t<> poller;

  zmq::socket_t socket(context, zmq::socket_type::pull);
  poller.add(socket, zmq::event_flags::pollin);
  socket.bind(own_address);

  std::vector<zmq::poller_event<>> events(100);

  while (app_running.load() == true) {

    events.resize(100);
    const auto event_n = poller.wait_all(events, timeout);

    {
      for (size_t i = 0; i < event_n; i++) {
        auto _ = std::unique_lock(internal_mutex);
        zmq::message_t mess;
        events[i].socket.recv(mess);
        incoming_messages.push_back(mess.to_string());
      }
    }
  }
}
