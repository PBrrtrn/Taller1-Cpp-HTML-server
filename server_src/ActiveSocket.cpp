#include <vector>
#include <iostream>

#include "ActiveSocket.h"

ActiveSocket::ActiveSocket(Socket&& socket, Protocol& protocol)	
													: socket(std::move(socket)), protocol(protocol) {
	this->talking = true;
}

ActiveSocket::~ActiveSocket() {
	this->socket.close();
	this->join();
}

void ActiveSocket::run() {
	this->protocol.handleSocket(this->socket);
	this->talking = false;
}
