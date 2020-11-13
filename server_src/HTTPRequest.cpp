#include <sstream>

#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(std::string message) {
	std::stringstream stream;
	stream << message;

	stream >> this->resource_name;
}

HTTPRequest::~HTTPRequest() { }

GetRequest::~GetRequest() { }

void GetRequest::print() {
	
}

HTTPResponse& GetRequest::execute(ResourceRepository& resources) {

}

PostRequest::PostRequest(std::string message) : HTTPRequest(message) {
	size_t begin = message.find("\n\n");
	this->body = message.substr(begin + 2, message.npos);
}

void PostRequest::print() {

}

HTTPResponse& PostRequest::execute(ResourceRepository& resources) {

}
