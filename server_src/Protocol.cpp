#include <sstream>
#include <iostream>

#include "Protocol.h"

Protocol::Protocol() {}

Protocol::~Protocol() {}

void HTMLProtocol::handleSocket(Socket& socket) {
	std::cout << "Handling socket" << std::endl;
}