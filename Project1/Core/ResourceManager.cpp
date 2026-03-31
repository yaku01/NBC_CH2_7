#include "ResourceManager.h"
#include <fstream>


std::optional<std::reference_wrapper<const std::deque<std::string>>> ResourceManager::GetResource(const std::string& file_path)
{
	// 이미 읽어온 파일이면 해당 내용 반환
	auto it = data.find(file_path);
	if (it != data.end()) {
		return it->second;
	}

	std::deque<std::string>& resource = data[file_path];
	std::ifstream in(file_path);
	
	// 파일이 없다면 nullopt 반환
	if (!in.is_open()) {
		return std::nullopt;
	}
	else {
		std::string line;
		while (std::getline(in, line)) {
			resource.push_back(line);
		}
	}

	return resource;
}
