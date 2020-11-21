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
  this->socket.shutdown_write();
  this->socket.close();
  this->join();
}

void ActiveSocket::run() {
  this->protocol.handleSocket(this->socket);
  // this->finished_talking = true;
}

/*
bool ActiveSocket::finishedTalking() {
  return this->finished_talking;
}
*/
