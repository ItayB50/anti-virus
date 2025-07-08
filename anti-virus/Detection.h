#pragma once
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

enum DetectionType
{
	Clean,
	Suspicious,
	Malicious
};

inline std::string detectionTypeToString(DetectionType type)
{
	switch (type)
	{
		case Clean: return "clean";
		case Suspicious: return "suspicious";
		case Malicious: return "malicious";
		default: return "unknown";
	}
}

struct Detection
{
	std::string file_path;
	size_t instances;
	DetectionType type;
	std::chrono::system_clock::time_point time_tag;


	inline std::string toPrint() const
	{
		std::ostringstream oss;
		std::time_t t = std::chrono::system_clock::to_time_t(time_tag);
		std::tm tm;
		localtime_s(&tm, &t);

		oss << "Detection - Path:" << file_path;
		oss << ", Type:" << detectionTypeToString(type);
		oss << ", Time:" << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
		oss << ", Instances:" << instances;

		return oss.str();
	}
};
