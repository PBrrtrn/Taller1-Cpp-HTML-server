#include "HTTPResponse.h"

HTTPResponse::HTTPResponse() { }

HTTPResponse::~HTTPResponse() { }

OKResponse::OKResponse(std::string body) : body(body) { }

OKResponse::~OKResponse() { }

std::string OKResponse::getResponse() { 
	return this->body;
}

ForbiddenResponse::ForbiddenResponse() { }

ForbiddenResponse::~ForbiddenResponse() { }

std::string ForbiddenResponse::getResponse() {
	return std::string("​HTTP/1.1 403 FORBIDDEN\n\n");
}

NotFoundResponse::NotFoundResponse() { }

NotFoundResponse::~NotFoundResponse() { }

std::string NotFoundResponse::getResponse() {
	return std::string("HTTP/1.1 404 NOT FOUND\n\n");
}

NotAllowedResponse::NotAllowedResponse() { }

NotAllowedResponse::~NotAllowedResponse() { }

std::string NotAllowedResponse::getResponse() {
	return std::string("HTTP/1.1 405 METHOD NOT ALLOWED\n\n");
}