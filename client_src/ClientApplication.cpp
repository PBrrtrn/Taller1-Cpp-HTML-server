#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

#include "ClientApplication.h"
#include "../common_src/Socket.h"

#define CHUNK_SIZE 64

ClientApplication::ClientApplication(const char* host, const char* port) {
	try { 
		this->socket.connect(host, port);
	}	catch (const char* error) { 
		std::cout << error << std::endl;
	}
}

ClientApplication::~ClientApplication() { }

void ClientApplication::run() {
	std::stringstream input_stream;
	input_stream << std::cin.rdbuf();
	std::string output = input_stream.str();

	this->socket.send(output.c_str(), output.length());
	this->socket.shutdown_write();

	std::stringstream output_stream;
	char response = 0;
	while (this->socket.receive(&response, 1) > 0)
		output_stream << response;

	std::cout << output_stream.str();
}
