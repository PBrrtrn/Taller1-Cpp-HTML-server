#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include <atomic>
#include <list>

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include "Protocol.h"
#include "ActiveSocket.h"

class AcceptorSocket : public Thread {
private:
	Protocol& protocol;
	Socket socket;
	std::atomic<bool>& server_running;
	std::list<ActiveSocket*> clients;
	void cleanup();
public:
	AcceptorSocket(const char* port, Protocol& protocol,
								 std::atomic<bool>& server_running);
	~AcceptorSocket() override;
	void run() override;
};

#endif
