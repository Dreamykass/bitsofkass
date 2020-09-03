
#include <spdlog/spdlog.h>

int main() {
  spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [%22!s:%3#] [t%t] -- %v");
  SPDLOG_INFO("main starts");

  SPDLOG_INFO("main ends");
  return 0;
}
