#ifndef __SERVER_APPLICATION_H__
#define __SERVER_APPLICATION_H__

#include <atomic>

#include "AcceptorSocket.h"
// #include "Protocol.h"

class ServerApplication {
private:
	std::atomic<bool> running;
	AcceptorSocket acceptor;
public:
	ServerApplication(const char *service);
	~ServerApplication();
	void rackup();
};

#endif
