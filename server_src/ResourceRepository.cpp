#include <string>

#include "File.h"
#include "ResourceRepository.h"

ResourceRepository::ResourceRepository(const char* root_contents_path) {
  File file(root_contents_path);
  this->resources[std::string("/")] = file.read();
}

ResourceRepository::~ResourceRepository() { }

void ResourceRepository::addResource(const std::string& resource_name,
                                    const std::string& resource) {
  const std::lock_guard<std::mutex> lock(this->mutex);
  this->resources[resource_name] = resource;
}

std::string ResourceRepository::getResource(const std::string& resource_name) {
  const std::lock_guard<std::mutex> lock(this->mutex);

  auto it = this->resources.find(resource_name);
  if (it != this->resources.end()) {
    return it->second;
  } else {
    throw std::runtime_error("Resource does not exist");
  }
}
