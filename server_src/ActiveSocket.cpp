#include <vector>
#include <iostream>

#include "ActiveSocket.h"

ActiveSocket::ActiveSocket(Socket&& socket)	: socket(std::move(socket)) {
	this->talking = true;
	std::cout << "Created active socket" << std::endl;
}

ActiveSocket::~ActiveSocket() {
	this->socket.close();
	this->join();
}

void ActiveSocket::run() {
	char response[5];
	this->socket.receive(response, 5);
	// std::vector<char> response = this->socket.receive();
	this->talking = false;
}
