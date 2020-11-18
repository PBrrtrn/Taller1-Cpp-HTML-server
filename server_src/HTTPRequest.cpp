/*
#include <sstream>
#include <iostream>

#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(std::string message) {
	std::stringstream stream;
	stream << message;

	stream >> this->resource_name;
}

HTTPRequest::~HTTPRequest() { }

GetRequest::GetRequest(std::string message) : HTTPRequest(message) { }

GetRequest::~GetRequest() { }

void GetRequest::print() {
	std::cout << "Get request" << std::endl;
}

HTTPResponse* GetRequest::execute(ResourceRepository& resources) {
	return new OKResponse(std::string("resource"));
}

PostRequest::PostRequest(std::string message) : HTTPRequest(message) {
	size_t begin = message.find("\n\n");
	this->body = message.substr(begin + 2, message.npos);
}

void PostRequest::print() {
	std::cout << "Post request" << std::endl;
}

HTTPResponse* PostRequest::execute(ResourceRepository& resources) {
	return new OKResponse(std::string("resource"));
}
*/