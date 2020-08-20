
#include "networker.hpp"
#include <map>
#include <zmq.hpp>

namespace {
  const std::chrono::milliseconds timeout{ 200 };
}

void networker_t::incoming_work() {
  zmq::context_t context;
  zmq::poller_t<> poller;

  std::map<std::string, zmq::socket_t> sockets;

  std::vector<zmq::poller_event<>> events(100);

  while (app_running.load() == true) {
    {
      auto _ = std::unique_lock(internal_mutex);

      // synchronize sockets with peers
      for (const auto& peer : peers) {
        if (!sockets.contains(peer)) {
          sockets[peer] =
            std::move(zmq::socket_t(context, zmq::socket_type::pull));
          sockets[peer].connect(peer);
        }
      }
    }

    events.resize(sockets.size());
    const auto event_n = poller.wait_all(events, timeout);

    {
      auto _ = std::unique_lock(internal_mutex);

      for (size_t i = 0; i < event_n; i++) {
        zmq::message_t mess;
        events[i].socket.recv(mess);
        incoming_messages.push_back(mess.to_string());
      }
    }
  }
}
