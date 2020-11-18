#include <sstream>
#include <iostream>

#include "Protocol.h"

#define BUFFER_SIZE 64

Protocol::Protocol() {}

Protocol::~Protocol() {}

HTTPProtocol::HTTPProtocol(ResourceRepository& resources) 
	: resources(resources) { }

void HTTPProtocol::handleSocket(Socket& socket) {
	std::cout << "Handling socket at HTTPProtocol!" << std::endl;
	std::stringstream stream;
	char buffer[BUFFER_SIZE] = {0};
	while (socket.receive(buffer, BUFFER_SIZE-1) != 0) stream << buffer;
	std::cout << stream.str() << std::endl;
	/*
	std::stringstream stream;
	char buffer[BUFFER_SIZE] = {0};
	while (socket.receive(buffer, BUFFER_SIZE-1) != 0) stream << buffer;

	std::string word;
	stream >> word;

	std::string resource_name;
	stream >> resource_name;

	if (word.compare("POST") == 0) {
		std::string message = stream.str();

		size_t begin = message.find("\n\n");
		size_t end = message.npos;

		std::string body = message.substr(begin + 2, end);

	} else if (word.compare("GET") == 0) {
		// request de get
	} else {
		// manejar el pedido invalido
	}
	*/
}
