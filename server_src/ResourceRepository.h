#ifndef __RESOURCE_REPOSITORY_H__
#define __RESOURCE_REPOSITORY_H__

#include <string>
#include <mutex>
#include <unordered_map>

class ResourceRepository {
private:
  std::mutex mutex;
  std::unordered_map<std::string, std::string> resources;
public:
  explicit ResourceRepository(const char *root_contents_path);
  ~ResourceRepository();
  ResourceRepository(const ResourceRepository&) = delete;            // Saco el constructor por copia
  ResourceRepository& operator=(const ResourceRepository&) = delete; // Saco la asignacion por copia
  int addResource(const std::string& resource_name,
                  const std::string& resource);
  const bool hasResource(const std::string&);
  const std::string getResource(const std::string& resource_name);
};

#endif
