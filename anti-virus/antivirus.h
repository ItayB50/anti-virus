#pragma once
#include <map>
#include <filesystem>
#include "Detection.h"
#include "../infra/infra.h"

class Antivirus
{
public:

	using Sha256_t = std::string;

	Antivirus(std::filesystem::path configPath, const int keyColumnIdx);

	// Non copyapble/moveable
	Antivirus& operator=(const Antivirus& other) = delete;
	Antivirus& operator=(Antivirus&& other) = delete;

	Antivirus(const Antivirus& other) = delete;
	Antivirus(Antivirus&& other) = delete;

	std::map<Sha256_t, Detection> ScanRunningProcesses();

private:
	bool LoadConfig(std::filesystem::path configPath, int keyColumnIdx);
	bool ValidateConfig(infra::ConfigurationMap_t config);
	
	infra::ConfigurationMap_t _config;
};

