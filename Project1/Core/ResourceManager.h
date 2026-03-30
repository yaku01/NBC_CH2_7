#pragma once
#include <string>
#include <unordered_map>
#include <deque>
#include <optional>
#include <functional>

class ResourceManager
{
public:
	static ResourceManager& GetInstance() {
		static ResourceManager instance;
		return instance;
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	
	std::optional<std::reference_wrapper<const std::deque<std::string>>> GetResource(const std::string& file_path);
	
private:
	std::unordered_map<std::string, std::deque<std::string>> data;

	ResourceManager() = default;
	~ResourceManager() = default;
};

