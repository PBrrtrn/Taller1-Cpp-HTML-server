#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <memory>

#include "ResourceRepository.h"
#include "HTTPResponse.h"

class HTTPRequest {
private:
	std::string resource_name;
public:
	HTTPRequest(std::string resource_name);
	virtual ~HTTPRequest();
	virtual std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) = 0;
};

class GetRequest : public HTTPRequest {
public:
	GetRequest(std::string resource_name);
	std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

class PostRequest : public HTTPRequest {
private:
	std::string resource_body;
public:
	PostRequest(std::string resource_name,
							std::string resource_body);
	std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

class BadRequest : public HTTPRequest {
	BadRequest(std::string resource_name);
	std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

#endif
