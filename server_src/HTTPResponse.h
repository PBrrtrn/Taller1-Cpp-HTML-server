#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <string>

class HTTPResponse {
public:
	HTTPResponse();
	virtual ~HTTPResponse();
	virtual std::string getResponse() = 0;
};

class OKResponse : public HTTPResponse {
private:
	std::string body;
public:
	OKResponse(std::string body);
	virtual ~OKResponse();
	virtual std::string getResponse();
};

class ForbiddenResponse : public HTTPResponse {
public:
	ForbiddenResponse();
	virtual ~ForbiddenResponse();
	virtual std::string getResponse();
};

class NotFoundResponse : public HTTPResponse {
public:
	NotFoundResponse();
	virtual ~NotFoundResponse();
	virtual std::string getResponse();
};

class NotAllowedResponse : public HTTPResponse {
public:
	NotAllowedResponse();
	virtual ~NotAllowedResponse();
	virtual std::string getResponse();
};

#endif
