#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <Windows.h>

namespace infra
{
	struct ProcessDescriptor
	{
		std::wstring name;
		std::filesystem::path path;
		DWORD pid;
	};

	std::vector<ProcessDescriptor> getRunningProcesses();
}
