#ifndef __SERVER_APPLICATION_H__
#define __SERVER_APPLICATION_H__

#include <atomic>

class ServerApplication {
private:
	std::atomic<bool> running;
	int port;
public:
	ServerApplication(const char *service);
	~ServerApplication();
	void rackup();
};

#endif
