#include <iostream>
#include <unistd.h>

#include "AcceptorSocket.h"

#define QUEUE_SIZE 5

AcceptorSocket::AcceptorSocket(const char* port, Protocol& protocol,
															 std::atomic<bool>& server_running)
	: protocol(protocol), server_running(server_running) {
	this->socket.bind(port);
	this->socket.listen(QUEUE_SIZE);
}

AcceptorSocket::~AcceptorSocket() {
	for (ActiveSocket* client : this->clients) delete client;

	this->socket.shutdown();
	this->socket.close();
	this->join();
}

void AcceptorSocket::run() {
	while (this->server_running) {
		Socket peer;
		try {
			peer = this->socket.accept();
		} catch (int) {
			std::cout << "closing acceptor socket" << std::endl;
			break;
		}
		ActiveSocket *active_socket = new ActiveSocket(std::move(peer), protocol);
		active_socket->start();
		this->clients.push_back(active_socket);

		// cleanup();
	}
}

void AcceptorSocket::cleanup() {
	auto it = this->clients.begin();
	while (it != clients.end()) {
		if ((*it)->finishedTalking()) {
			delete *it;
			clients.erase(it);
		} else {
			it++;
		}
	}
}
