#include <map>

#include "antivirus.h"


Antivirus::Antivirus(std::filesystem::path configPath, const int keyColumnIdx)
{
    if (!LoadConfig(configPath, keyColumnIdx))
    {
        throw std::invalid_argument("Failed to load configuration file, configuration is invalid");
    }
}

bool Antivirus::LoadConfig(std::filesystem::path configPath, int keyColumnIdx)
{
	auto config = infra::readCsv(configPath, keyColumnIdx);
	bool isValid = ValidateConfig(config);
    if (isValid)
    {
        _config = std::move(config);
    }
	return isValid;
}

bool Antivirus::ValidateConfig(infra::ConfigurationMap_t config)
{
	bool isValid = (config.size() > 0);

	// Add more validations here as needed

	return isValid;
}

std::map<Antivirus::Sha256_t, Detection> Antivirus::ScanRunningProcesses()
{
    // Order of values in config
    const int procNameIdx = 0;
    const int sha256Idx = 1;
    
    std::map<Antivirus::Sha256_t, Detection> detections;
    auto runningProcesses = infra::getRunningProcesses();

    for (const auto& p : runningProcesses)
    {
        std::string strFilePath = p.path.u8string();
        auto mapIter = _config.find(strFilePath);
        if (mapIter != _config.end())
        {
            const std::vector<std::string>& row = mapIter->second;

            // Probably a redundant column
            std::string strMaliciousProcName = row[procNameIdx];

            std::string strMaliciousImageSha256 = row[sha256Idx];

            // Calc hash only in case of path match, to avoid un-neccesary heavy calculations
            const std::string strProcImageSha256 = infra::getSha256(p.path);

            // Fill detection details
            detections[strProcImageSha256].file_path = strFilePath;
            ++detections[strProcImageSha256].instances;
            detections[strProcImageSha256].time_tag = std::chrono::system_clock::now();
            detections[strProcImageSha256].type = DetectionType::Suspicious;

            if (strProcImageSha256 == strMaliciousImageSha256)
            {
                // Detection!
                detections[strProcImageSha256].type = DetectionType::Malicious;
            }
        }
    }

    return detections;
}
