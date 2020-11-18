#include <iostream>

#include "ServerApplication.h"

ServerApplication::ServerApplication(const char* service) : 
	running(false), acceptor(service, running) {
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
