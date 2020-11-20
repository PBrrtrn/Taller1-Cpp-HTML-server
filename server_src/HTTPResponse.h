#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <string>

struct HTTPResponse {
public:
	HTTPResponse();
	virtual ~HTTPResponse();
	virtual std::string getResponse() = 0;
};

struct OKResponse : public HTTPResponse {
private:
	std::string body;
public:
	explicit OKResponse(std::string body);
	std::string getResponse() override;
};

struct ForbiddenResponse : public HTTPResponse {
	std::string getResponse() override;
};

struct NotFoundResponse : public HTTPResponse {
	std::string getResponse() override;
};

struct NotAllowedResponse : public HTTPResponse {
private:
	std::string method_called;
public:
	explicit NotAllowedResponse(std::string method_called);
	std::string getResponse() override;
};

#endif
