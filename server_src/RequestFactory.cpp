#include <sstream>
#include <iostream>

#include "RequestFactory.h"

RequestFactory::RequestFactory() { }

RequestFactory::~RequestFactory() { }

std::unique_ptr<HTTPRequest> RequestFactory::operator()(std::string& message) {
  std::stringstream stream(message);

  std::string method;
  std::string resource_name;
  stream >> method;
  stream >> resource_name;

  return build(message, method, resource_name);
}

std::unique_ptr<HTTPRequest> RequestFactory::build
                             (const std::string& message,
                              const std::string& method,
                              const std::string& resource_name) {
  std::unique_ptr<HTTPRequest> ptr;

  if (method.compare("POST") == 0) {
    size_t begin = message.find("\n\n");
    std::string resource_body = message.substr(begin + 2, message.npos);
    ptr.reset(new PostRequest(resource_name, resource_body));
  } else if (method.compare("GET") == 0) {
    ptr.reset(new GetRequest(resource_name));
  } else {
    ptr.reset(new BadRequest(resource_name, method));
  }

  return ptr;
}
