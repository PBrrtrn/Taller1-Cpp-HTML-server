#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include <atomic>
#include <list>

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include "ActiveSocket.h"

class AcceptorSocket : public Thread {
private:
	std::atomic<bool>& server_running;
	Socket socket;
	std::list<ActiveSocket*> clients;
	void cleanup();
public:
	AcceptorSocket(const char* port, 
								 std::atomic<bool>& server_running);
	~AcceptorSocket() override;
	void run() override;
};

#endif
