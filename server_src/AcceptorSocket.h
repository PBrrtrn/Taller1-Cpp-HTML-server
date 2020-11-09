#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"

class AcceptorSocket : public Thread {
private:
	Socket socket;
	std::atomic<bool>& running;
public:
	AcceptorSocket(int port, std::atomic<bool>& running);
	void run();
	~AcceptorSocket();
};

#endif
