#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>

#include "HTTPResponse.h"
#include "ResourceRepository.h"

class HTTPRequest {
private:
	std::string resource_name;
public:
	HTTPRequest(std::string message);
	virtual ~HTTPRequest();
	virtual HTTPResponse& execute(ResourceRepository& resources) = 0;
	virtual void print() = 0;
};

class GetRequest : public HTTPRequest {
public:
	virtual ~GetRequest();
	virtual HTTPResponse& execute(ResourceRepository& resources);
	virtual void print();
};

class PostRequest : public HTTPRequest {
private:
	std::string body;
public:
	PostRequest(std::string message);
	virtual ~PostRequest();
	virtual HTTPResponse& execute(ResourceRepository& resources);
	virtual void print();
};

#endif
