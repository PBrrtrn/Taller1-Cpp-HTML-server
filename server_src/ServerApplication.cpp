#include <iostream>
#include <sstream>

#include "ServerApplication.h"
#include "AcceptorSocket.h"

ServerApplication::ServerApplication(const char* service) {
	std::stringstream port_string;
	port_string << service;
	port_string >> this->port;

	this->running = false;
}

ServerApplication::~ServerApplication() { }

void ServerApplication::rackup() {
	this->running = true;

	AcceptorSocket acceptor(this->port);

	while (this->running) {
		char user_input = getchar();
		if (user_input == 'q') this->running = false;
	}

}
