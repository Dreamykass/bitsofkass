#pragma once

#include <thread>
#include <chrono>
#include <string>
#include <spdlog/spdlog.h>
#include <fmt/format.h>

#include "shared_data.hpp"
#include "cppzmq_incl.hpp"

void incoming_work(SharedData& _shared_data) {
  SPDLOG_INFO("incoming_work starts");

  zmq::context_t context;
  zmq::poller_t<> poller;

  zmq::socket_t socket(context, zmq::socket_type::pull);
  std::string current_address = _shared_data.GetOwnAddress();

  socket.bind(current_address);
  poller.add(socket, zmq::event_flags::pollin);

  std::vector<zmq::poller_event<>> events(100);

  while (_shared_data.app_should_close.load() == false) {

    // events.resize(100);

    // using namespace std::chrono_literals;
    // const auto event_n = poller.wait_all(events, 500ms);

    // for (size_t i = 0; i < event_n; i++) {
    //   zmq::message_t mess;
    //   events[i].socket.recv(mess);

    //   // ---
    //   evi::SystemString ss;
    //   ss.str = mess.to_string();

    //   evi::EventInternal ev = ss;
    //   _shared_data.events_for_gui.enqueue(ev);
    // }

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1ms);
  }

  SPDLOG_INFO("incoming_work ends");
}
