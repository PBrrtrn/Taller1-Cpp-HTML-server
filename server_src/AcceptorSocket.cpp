#include <iostream>
#include <unistd.h>
#include <utility>

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
    } catch (std::runtime_error& e) {
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
