
#include <functional>

class MyScopeExit {
private:
  std::function<void()> m_fun;

public:
  MyScopeExit(std::function<void()> _fun) { m_fun = _fun; }
  ~MyScopeExit() { m_fun(); }
};