#include <iostream>
#include <sstream>

#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(const std::string& resource_name) 
  : resource_name(resource_name) { }

HTTPRequest::~HTTPRequest() { }

GetRequest::GetRequest(const std::string& resource_name) 
  : HTTPRequest(resource_name) { }

std::unique_ptr<HTTPResponse> GetRequest::execute(ResourceRepository& repo) {
  std::cout << "GET " + this->resource_name + " HTTP/1.1" << std::endl;

  std::unique_ptr<HTTPResponse> ptr;
  if (repo.hasResource(this->resource_name)) {
    std::string resource = repo.getResource(this->resource_name);
    std::stringstream text;
    text << "Content-Type: text/html\n\n";
    text << resource;
    ptr.reset(new OKResponse(text.str()));
  } else {
    ptr.reset(new NotFoundResponse);
  }
  return ptr;
}

PostRequest::PostRequest(const std::string& resource_name,
                         const std::string& resource_body)
  : HTTPRequest(resource_name), resource_body(resource_body) { }

std::unique_ptr<HTTPResponse> PostRequest::execute(ResourceRepository& repo) {
  std::cout << "POST " + this->resource_name + " HTTP/1.1" << std::endl;

  std::unique_ptr<HTTPResponse> ptr(new NotFoundResponse);
  if (this->resource_name.compare(std::string("/")) == 0) {
    ptr.reset(new ForbiddenResponse);
  } else {
    repo.addResource(this->resource_name, this->resource_body);
    std::stringstream text;
    text << "\n";
    text << this->resource_body;
    ptr.reset(new OKResponse(text.str()));
  }
  return ptr;
}

BadRequest::BadRequest(const std::string& resource_name, 
                       const std::string& invalid_method)
  : HTTPRequest(resource_name), invalid_method(invalid_method) { }

std::unique_ptr<HTTPResponse> BadRequest::execute(ResourceRepository& repo) {
  std::string output = this->invalid_method + " " 
                     + this->resource_name + " HTTP/1.1";
  std::cout << output << std::endl;
  std::unique_ptr<HTTPResponse> ptr(new NotAllowedResponse(invalid_method));
  return ptr;
}
