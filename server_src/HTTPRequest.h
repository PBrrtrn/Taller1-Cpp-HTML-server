#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <string>
#include <memory>

#include "ResourceRepository.h"
#include "HTTPResponse.h"

class HTTPRequest {
protected:
  std::string resource_name;
public:
  explicit HTTPRequest(const std::string& resource_name);
  virtual ~HTTPRequest();
  virtual std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) = 0;
};

class GetRequest : public HTTPRequest {
public:
  explicit GetRequest(std::string& resource_name);
  std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

class PostRequest : public HTTPRequest {
private:
  std::string resource_body;
public:
  PostRequest(const std::string& resource_name,
              const std::string& resource_body);
  std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

class BadRequest : public HTTPRequest {
private:
  std::string invalid_method;
public:
  BadRequest(const std::string& resource_name, 
             const std::string& invalid_method);
  std::unique_ptr<HTTPResponse> execute(ResourceRepository& repo) override;
};

#endif
