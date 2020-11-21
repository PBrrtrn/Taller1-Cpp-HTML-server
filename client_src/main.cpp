#include <iostream>

#include "ClientApplication.h"

int main(int argc, const char* argv[]) {
  try {
    ClientApplication app(argv[1], argv[2]);
    app.run();
  } catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}
