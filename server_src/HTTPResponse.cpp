#include "HTTPResponse.h"

OKResponse::OKResponse(std::string body) : body(body) { }

OKResponse::~OKResponse() { }

std::string OKResponse::getResponse() { 
	return std::string("el pepe");
}

ForbiddenResponse::ForbiddenResponse() { }

ForbiddenResponse::~ForbiddenResponse() { }