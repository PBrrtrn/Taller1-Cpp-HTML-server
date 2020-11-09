#ifndef __SOCKET_H__
#define __SOCKET_H__

class Socket {
private:
	int fd;
public:
	Socket(const char *host, int port);
	~Socket();
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);
	// Faltan implementar TODOS los métodos de la interfaz de socket
};

#endif