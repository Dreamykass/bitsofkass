
#include <deferred_heap.h>
#include <iostream>
#include <string>
#include <memory>

void write(std::string _str) {
  std::cout << _str;
}

class foo {
public:
  int data;
  foo() { write("foo constructed\n"); }
  ~foo() { write("foo destructed\n"); }
};

int main() {
  write("start\n");

  gcpp::deferred_heap dheap;

  write("sizeof(deferred_ptr<foo>): " +
        std::to_string(sizeof(dheap.make<foo>())) + "\n");
  write("sizeof(unique_ptr<foo>): " +
        std::to_string(sizeof(std::make_unique<foo>())) + "\n");
  write("deferred heap created\n");

  {
    auto dptr = dheap.make<foo>();

    write("deferred pointer created\n");

    dptr->data;
  }

  write("deferred pointer destroyed\n");

  write("returning from main\n");

  return 0;
}
