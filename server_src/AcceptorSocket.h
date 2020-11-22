#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include <list>

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include "Protocol.h"
#include "ActiveSocket.h"

class AcceptorSocket : public Thread {
private:
  Protocol& protocol;
  Socket socket;
  std::list<ActiveSocket*> clients;
  void cleanup();
public:
  AcceptorSocket(const char* port, Protocol& protocol);
  ~AcceptorSocket() override;
  void run() override;
};

#endif
