#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include "ActiveSocket.h"
#include "../common_src/Socket.h"
#include "../common_src/Thread.h"

class AcceptorSocket : public Thread {
private:
	Socket socket;
	std::vector<ActiveSocket*> active_sockets;
	std::atomic<bool>& running;
public:
	AcceptorSocket(const char *port, std::atomic<bool>& running);
	~AcceptorSocket();
	void run();
	void shutdown();
};

#endif
