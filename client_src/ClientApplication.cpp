#include <iostream>
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
	char buffer[CHUNK_SIZE];
	FILE *file = stdin;
	while (feof(file) == 0) {
		memset(buffer, '\0', CHUNK_SIZE);
		int bytes_read = fread(buffer, sizeof(char), CHUNK_SIZE, file);

		this->socket.send(buffer, bytes_read);
	}
}
