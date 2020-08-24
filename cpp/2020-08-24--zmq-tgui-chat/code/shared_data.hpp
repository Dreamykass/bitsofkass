#pragma once

#include "misc.hpp"
#include <concurrentqueue/blockingconcurrentqueue.h>

struct shared_data {
  safe_string own_ip;
  safe_string own_port;
  safe_string own_address;

  moodycamel::BlockingConcurrentQueue bq;
};
