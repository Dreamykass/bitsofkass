
#include <string>
#include <functional>

void pretty_print(std::string _color, std::string _message);

class at_scope_exit {
private:
  std::function<void()> f;

public:
  at_scope_exit(std::function<void()> _f) { f = _f; };
  ~at_scope_exit() { f(); }
};