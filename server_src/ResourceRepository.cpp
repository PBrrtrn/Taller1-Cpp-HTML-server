#include "ResourceRepository.h"

ResourceRepository::ResourceRepository(std::string root_contents) {
	
}

ResourceRepository::~ResourceRepository() { }

int ResourceRepository::addResource(std::string resource_name,
																						 std::string resource) {
	mutex.lock();

	mutex.unlock();
	return 0;
}

std::string ResourceRepository::getResource(std::string resource_name) {
	mutex.lock();

	mutex.unlock();
	return std::string("OK");
}
