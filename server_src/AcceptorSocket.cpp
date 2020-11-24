#include <iostream>
#include <unistd.h>
#include <utility>

#include "AcceptorSocket.h"

#define QUEUE_SIZE 5

AcceptorSocket::AcceptorSocket(const char* port, Protocol& protocol)
  : protocol(protocol) {
  try {
    this->socket.bind(port);
    this->socket.listen(QUEUE_SIZE);
  } catch (SocketError& e) {
    std::cout << "ERROR: Could not bind to port " << port << std::endl;
    this->socket.close();
  }
}

AcceptorSocket::~AcceptorSocket() {
  for (ActiveSocket* client : this->clients) delete client;

  this->socket.shutdown();
  this->socket.close();
  this->join();
}

void AcceptorSocket::run() {
  while (true) {
    Socket peer;
    try {
      peer = this->socket.accept();
    } catch (SocketError& e) {
      break;
    }
    ActiveSocket *active_socket = new ActiveSocket(std::move(peer), protocol);
    this->clients.push_back(active_socket);
    active_socket->start();

    cleanup();
  }
}

void AcceptorSocket::cleanup() {
  auto it = this->clients.begin();
  while (it != clients.end()) {
    if ((*it)->finishedTalking()) {
      delete *it;
      it = clients.erase(it);
    } else {
      it++;
    }
  }
}
