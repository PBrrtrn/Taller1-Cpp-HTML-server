#include <cstring>
#include <iostream>

#include "AddrinfoWrapper.h"

AddrinfoWrapper::AddrinfoWrapper(const char *host, 
																 const char* service, 
																 int flags) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = flags;

  if (getaddrinfo(host, service, &hints, &(this->addresses)) != 0)
  	throw std::runtime_error("Error in getaddrinfo");
}

AddrinfoWrapper::~AddrinfoWrapper() {
	freeaddrinfo(this->addresses);
}
