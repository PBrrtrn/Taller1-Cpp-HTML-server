#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "../common_src/Socket.h"
#include "ResourceRepository.h"

class Protocol {
public:
	Protocol();
	virtual ~Protocol();
	virtual void handleSocket(Socket& socket) = 0;
};

class HTTPProtocol : public Protocol {
private:
	ResourceRepository& resources;
public:
	HTTPProtocol(ResourceRepository& resources);
	void handleSocket(Socket& socket);
};

#endif
