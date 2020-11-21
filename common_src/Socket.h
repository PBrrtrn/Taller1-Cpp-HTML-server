#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

class Socket {
private:
	int fd;
public:
	Socket();
	~Socket();
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);
	int bind(const char *service);
	int connect(const char *host, const char *service);
	int listen(int queue_size);
	Socket accept();
	int send(const char *data, size_t data_size);
	int receive(char *buffer, size_t n_bytes);
	void shutdown();
	void shutdown_write();
	void close();
};

#endif
