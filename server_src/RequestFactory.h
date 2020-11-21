#ifndef __REQUEST_FACTORY_H__
#define __REQUEST_FACTORY_H__

#include <string>
#include <memory>

#include "HTTPRequest.h"

class RequestFactory {
private:
  std::unique_ptr<HTTPRequest> build(std::string message,
                                     std::string method,
                                     std::string resource_name);
public:
  RequestFactory();
  ~RequestFactory();
  std::unique_ptr<HTTPRequest> operator()(std::string message);
};

#endif
