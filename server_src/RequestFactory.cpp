#include <sstream>
#include <iostream>

#include "RequestFactory.h"

RequestFactory::RequestFactory() { }

RequestFactory::~RequestFactory() { }

std::unique_ptr<HTTPRequest> RequestFactory::operator()(std::string message) {
	std::unique_ptr<HTTPRequest> ptr;

	std::stringstream stream(message);

	std::string word;
	std::string resource_name;
	stream >> word;
	stream >> resource_name;

	if (word.compare("POST") == 0) {
		size_t begin = message.find("\n\n");
		size_t end = message.npos;
		std::string resource_body = message.substr(begin + 2, end);

		ptr.reset(new PostRequest(resource_name, resource_body));
	} else if (word.compare("GET") == 0) {
		ptr.reset(new GetRequest(resource_name));
	} else {
		
	}

	std::cout << word + " " + resource_name + " HTTP/1.1" << std::endl;

	return ptr;
}
