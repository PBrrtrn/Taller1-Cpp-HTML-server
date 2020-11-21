#ifndef __CLIENT_APPLICATION_H__
#define __CLIENT_APPLICATION_H__

#include "../common_src/Socket.h"

class ClientApplication {
private:
  Socket socket;
public:
  ClientApplication(const char* host, const char* port);
  ~ClientApplication();
  void run();
};

#endif
