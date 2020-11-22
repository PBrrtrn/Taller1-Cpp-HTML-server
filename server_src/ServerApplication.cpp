#include <iostream>

#include "ServerApplication.h"

ServerApplication::ServerApplication(const char* service, 
                                     const char* root_contents) 
  : resources(root_contents), protocol(resources),
    acceptor(service, protocol) {}

ServerApplication::~ServerApplication() {}

void ServerApplication::rackup() {
  bool running = true;
  this->acceptor.start();
  while (running) {
    char user_input = getchar();
    if (user_input == 'q') running = false;
  }
}
