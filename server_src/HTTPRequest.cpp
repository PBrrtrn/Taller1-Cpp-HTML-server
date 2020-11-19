#include <iostream>

#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(std::string resource_name) 
	: resource_name(resource_name) { }

HTTPRequest::~HTTPRequest() { }

GetRequest::GetRequest(std::string resource_name) 
	: HTTPRequest(resource_name) { }

std::unique_ptr<HTTPResponse> GetRequest::execute(ResourceRepository& repo) {
	// Implementar
	std::unique_ptr<HTTPResponse> ptr(new NotFoundResponse);
	return ptr;
}

PostRequest::PostRequest(std::string resource_name, std::string resource_body)
	: HTTPRequest(resource_name), resource_body(resource_body) { }

std::unique_ptr<HTTPResponse> PostRequest::execute(ResourceRepository& repo) {
	// Impĺementar
	std::unique_ptr<HTTPResponse> ptr(new NotFoundResponse);
	return ptr;
}

BadRequest::BadRequest(std::string resource_name)
  : HTTPRequest(resource_name) { }

std::unique_ptr<HTTPResponse> BadRequest::execute(ResourceRepository& repo) {
	std::unique_ptr<HTTPResponse> ptr(new NotAllowedResponse);
	return ptr;
}
