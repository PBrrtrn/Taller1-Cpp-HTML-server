#ifndef __ACTIVE_SOCKET_H__
#define __ACTIVE_SOCKET_H__

#include "Thread.h"
#include "Socket.h"

class ActiveSocket : public Thread {
private:
	Socket socket;
public:
	ActiveSocket(int fd);
	void run();
};

#endif