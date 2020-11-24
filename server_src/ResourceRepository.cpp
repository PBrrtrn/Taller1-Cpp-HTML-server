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
    throw ResourceNotFoundError("Resource does not exist");
  }
}

ResourceNotFoundError::ResourceNotFoundError
      (const char* resource_name) noexcept {
  snprintf(this->error_msg, BUF_LEN, "Resource not found: %s", resource_name);
}

const char* ResourceNotFoundError::what() const noexcept {
  return this->error_msg;
}

ResourceNotFoundError::~ResourceNotFoundError() noexcept {}
