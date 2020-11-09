#ifndef __SERVER_APPLICATION_H__
#define __SERVER_APPLICATION_H__

class ServerApplication {
private:
	bool running;
	int port;
public:
	ServerApplication(const char *service);
	~ServerApplication();
	void rackup();
};

#endif
