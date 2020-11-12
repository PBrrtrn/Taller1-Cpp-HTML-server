#include <iostream>

#include "ClientApplication.h"
#include "../common_src/Socket.h"

ClientApplication::ClientApplication(const char* host, const char* port) {
	try { 
		this->socket.connect(host, port);
	}	catch (const char* error) { 
		std::cout << error << std::endl;
	}
}

ClientApplication::~ClientApplication() { }

void ClientApplication::run() {
	this->socket.send("Hola", 4);
}
