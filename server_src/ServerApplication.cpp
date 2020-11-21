#include <iostream>

#include "ServerApplication.h"

ServerApplication::ServerApplication(const char* service, 
                                     const char* root_contents) 
  : running(false), resources(root_contents), 
    protocol(resources), acceptor(service, protocol, running) {
}

ServerApplication::~ServerApplication() {}

void ServerApplication::rackup() {
  this->running = true;
  this->acceptor.start();
  while (running) {
    char user_input = getchar();
    if (user_input == 'q') this->running = false;
  }
}
