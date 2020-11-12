#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "../common_src/Socket.h"

class Protocol {
public:
	Protocol();
	virtual ~Protocol();
	virtual void handleSocket(Socket& socket) = 0;
};

class HTMLProtocol : public Protocol {
private:
	Socket socket;
public:
	void handleSocket(Socket& socket);
};

#endif