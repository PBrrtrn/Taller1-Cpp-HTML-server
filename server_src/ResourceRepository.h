#ifndef __RESOURCE_REPOSITORY_H__
#define __RESOURCE_REPOSITORY_H__

#include <mutex>
#include <unordered_map>

class ResourceRepository {
private:
	std::mutex mutex;
	std::unordered_map<std::string, std::string> resources;
public:
	ResourceRepository(const char *root_contents);
	~ResourceRepository();
	int addResource(std::string resource_name, std::string resource);
	const std::string getResource(std::string resource_name);
};

#endif