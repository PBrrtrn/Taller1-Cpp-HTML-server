#include <sstream>
#include <memory>
#include <iostream>

#include "Protocol.h"
#include "HTTPResponse.h"
#include "HTTPRequest.h"

#define BUFFER_SIZE 64

Protocol::Protocol() {}

Protocol::~Protocol() {}

HTTPProtocol::HTTPProtocol(ResourceRepository& resources) 
	: resources(resources), request_factory() { }

void HTTPProtocol::handleSocket(Socket& socket) {
	std::stringstream stream;
	char buffer[BUFFER_SIZE] = {0};
	while (socket.receive(buffer, BUFFER_SIZE-1) != 0) stream << buffer;

	std::unique_ptr<HTTPRequest> request = request_factory(stream.str());
	std::unique_ptr<HTTPResponse> response = request->execute(this->resources);

	std::string response_string = response->getResponse();

	std::cout << response_string << std::endl;
}
