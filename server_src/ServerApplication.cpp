#include <iostream>
#include <sstream>
#include <atomic>

#include "ServerApplication.h"
#include "AcceptorSocket.h"

ServerApplication::ServerApplication(const char* service) {
	this->port = service;
	this->running = false;
}

ServerApplication::~ServerApplication() { }

void ServerApplication::rackup() {
	this->running = true;

	AcceptorSocket acceptor(this->port, this->running);
	acceptor.start();

	while (this->running) {
		char user_input = getchar();
		if (user_input == 'q') this->running = false;
	}

	acceptor.join();
}
