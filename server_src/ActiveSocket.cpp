#include <iostream>
#include <utility>
#include <sstream>

#include "ActiveSocket.h"

#define BUFFER_SIZE 64

ActiveSocket::ActiveSocket(Socket socket, Protocol& protocol)
  : protocol(protocol) {
  this->socket = std::move(socket);
}

ActiveSocket::~ActiveSocket() {
  this->socket.close();
  this->join();
}

void ActiveSocket::run() {
  this->protocol.handleSocket(this->socket);
  socket.shutdown();
  this->finished_talking = true;
}

bool ActiveSocket::finishedTalking() const {
  return this->finished_talking;
}
