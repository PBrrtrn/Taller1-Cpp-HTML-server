#include "ResourceRepository.h"

ResourceRepository::ResourceRepository(const char* root_contents) {
	this->resources[std::string("/")] = root_contents;
}

ResourceRepository::~ResourceRepository() { }

int ResourceRepository::addResource(std::string resource_name,
																		std::string resource) {
	const std::lock_guard<std::mutex> lock(this->mutex);
	this->resources[resource_name] = resource;
	return 0;
}

const bool ResourceRepository::hasResource(std::string resource_name) {
	const std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->resources.find(resource_name);
	return (!(it == resources.end()));
}

const std::string ResourceRepository::getResource(std::string resource_name) {
	const std::lock_guard<std::mutex> lock(this->mutex);
	return this->resources[resource_name];
}
