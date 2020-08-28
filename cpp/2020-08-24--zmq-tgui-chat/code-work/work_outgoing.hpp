#pragma once

#include <spdlog/spdlog.h>

#include "shared_data.hpp"

void outgoing_work(SharedData& _shared_data) {
  SPDLOG_INFO("outgoing_work starts");

  while (_shared_data.app_should_close.load() == false) {
    evi::EventInternal event;
    _shared_data.events_for_outgoing.wait_dequeue(event);
  }

  SPDLOG_INFO("outgoing_work ends");
}
