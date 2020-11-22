#ifndef __SERVER_APPLICATION_H__
#define __SERVER_APPLICATION_H__

#include "AcceptorSocket.h"
#include "ResourceRepository.h"
#include "Protocol.h"

class ServerApplication {
private:
  ResourceRepository resources;
  HTTPProtocol protocol;
  AcceptorSocket acceptor;
public:
  ServerApplication(const char *service, const char *root_contents);
  ~ServerApplication();
  void rackup();
};

#endif
