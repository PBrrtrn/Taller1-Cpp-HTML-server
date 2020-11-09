#include <iostream>

#include "AcceptorSocket.h"
#include "../common_src/Socket.h"

AcceptorSocket::AcceptorSocket(int port) : socket(NULL, port) {
	std::cout << "Created acceptor socket!" << std::endl;
}

AcceptorSocket::~AcceptorSocket() {
	std::cout << "Freed acceptor socket!" << std::endl;
}
