#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace infra
{
	using ConfigurationMap_t = std::unordered_map<std::string, std::vector<std::string>>;

	ConfigurationMap_t readCsv(std::filesystem::path filePath, int keyColumnIdx = 0);
}
