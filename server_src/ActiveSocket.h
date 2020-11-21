#ifndef __ACTIVE_SOCKET_H__
#define __ACTIVE_SOCKET_H__

#include "../common_src/Thread.h"
#include "../common_src/Socket.h"
#include "Protocol.h"

class ActiveSocket : public Thread {
private:
  Protocol& protocol;
  bool finished_talking = false;
  Socket socket;
public:
  ActiveSocket(Socket socket, Protocol& protocol);
  ~ActiveSocket();
  void run() override;
  bool finishedTalking();
};

#endif
