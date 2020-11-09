#include <sys/socket.h> 
#include <iostream>
#include <utility>

#include "Socket.h"

Socket::Socket(const char *host, int port) {
	this->fd = -1;
	std::cout << "Starting socket on port " << port << std::endl;
	// Acá llamaría a los métodos privados bind y listen...
}

Socket::Socket(Socket&& other) {
	this->fd = std::move(other.fd);
}

Socket& Socket::operator=(Socket&& other) {
	this->fd = std::move(other.fd);
	return *this;
}

Socket::~Socket() {
	// Acá haría close del file descriptor
	std::cout << "Closing and freeing socket " << std::endl;
}
