#include <iostream>
#include <sstream>

#include "ActiveSocket.h"

#define BUFFER_SIZE 64

ActiveSocket::ActiveSocket(Socket socket) {
	this->socket = std::move(socket);
}

ActiveSocket::~ActiveSocket() {
	this->socket.shutdown();
	this->socket.close();
	this->join();
	std::cout << "closing active socket" << std::endl;
}

void ActiveSocket::run() {
	std::stringstream stream;
	char buffer[BUFFER_SIZE] = {0};
	while (socket.receive(buffer, BUFFER_SIZE-1) != 0) stream << buffer;
	std::cout << stream.str() << std::endl;
	this->finished_talking = true;
}

bool ActiveSocket::finishedTalking() {
	return this->finished_talking;
}
