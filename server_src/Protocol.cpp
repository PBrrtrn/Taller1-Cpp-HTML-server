#include <sstream>
#include <string>
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

void HTTPProtocol::handleSocket(const Socket& socket) {
  std::stringstream stream;
  char buffer = '\0';
  while (socket.receive(&buffer, 1) != 0) stream << buffer;
  std::string request_text = stream.str();
  std::unique_ptr<HTTPRequest> request = request_factory(request_text);

  std::unique_ptr<HTTPResponse> response = request->execute(this->resources);
  std::string response_string = response->getResponse();

  socket.send(response_string.c_str(), response_string.length());
}
