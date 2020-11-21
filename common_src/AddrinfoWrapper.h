#ifndef __ADDRINFO_WRAPPER_H__
#define __ADDRINFO_WRAPPER_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

struct AddrinfoWrapper {
	struct addrinfo *addresses;
	AddrinfoWrapper(const char *host, const char* service, int flags);
	~AddrinfoWrapper();
};

#endif