#ifndef __REQUEST_FACTORY_H__
#define __REQUEST_FACTORY_H__

#include <string>
#include <memory>

#include "HTTPRequest.h"

class RequestFactory {
private:
  std::unique_ptr<HTTPRequest> build(const std::string& message,
                                     const std::string& method,
                                     const std::string& resource_name);
public:
  RequestFactory();
  ~RequestFactory();
  std::unique_ptr<HTTPRequest> operator()(std::string& message);
};

#endif
