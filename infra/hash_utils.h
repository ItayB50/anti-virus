#pragma once
#include <string>

namespace infra
{
	std::string getSha256(std::filesystem::path filePath);
}
