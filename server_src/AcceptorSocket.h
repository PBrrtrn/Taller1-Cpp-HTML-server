#ifndef __ACCEPTOR_SOCKET_H__
#define __ACCEPTOR_SOCKET_H__

#include "../common_src/Socket.h"

class AcceptorSocket {
private:
	Socket socket;
public:
	AcceptorSocket(int port);
	~AcceptorSocket();
};

#endif
