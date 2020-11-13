#include <sstream>
#include <iostream>

#include "Protocol.h"
#include "HTTPRequest.h"

#define BUFFER_SIZE 64

Protocol::Protocol() {}

Protocol::~Protocol() {}

HTTPProtocol::HTTPProtocol(ResourceRepository &resources) 
													 : resources(resources) { }

void HTTPProtocol::handleSocket(Socket& socket) {
	/* El socket recibido es un recurso compartido porque el AcceptorSocket
	va a intentar cerrarlo en algún punto, así que hay que protegerlo de 
	alguna manera
	-> Quizás una condition variable? */
	std::stringstream stream;
	char buffer[BUFFER_SIZE] = {0};
	while (socket.receive(buffer, BUFFER_SIZE-1) != 0) stream << buffer;

	std::string word;
	stream >> word;
	/*
	HTTPRequest& request;

	if (word.compare("GET") == 0) {
		request = GetRequest(stream.str());
	} else if (world.compare("POST") == 0) {
	
	}
	*/
	std::string resource_name;
	stream >> resource_name;

	if (word.compare("POST") == 0) {
		std::string message = stream.str();

		size_t begin = message.find("Content-Length:");
		size_t end = message.find('\n', begin);
		std::stringstream content_length(message.substr(begin + 16, end - begin - 16));

		size_t size;
		content_length >> size;

		begin = message.find("\n\n");
		end = message.npos;

		std::string body = message.substr(begin + 2, end);

	} else if (word.compare("GET") == 0) {
		// request de get
	} else {
		// manejar el pedido invalido
	}
}
