# anti-virus

Simple C++ anti-virus library

## Platforms
* Windows (msvc)

## Package managers:
* TODO

## Features
* Detects malicious running processes according to a predefined CSV file

## Future Ideas

- Add fast and robust logging library like spdlog
- Use openssl for hash calculations (repleace current header only hash utils)
- Provide UI to generate and validate configuration file
- Implement multithreaded scanning to improve performance 
- Add real-time process monitoring using low-level driver or ETW  
- Integration with package manager like Conan


## Usage samples

#### Basic usage
```c++
#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>
#include "../anti-virus/antivirus.h"

int main()
{
    try
    {
        const int keyColumn = 1; // Key column is the path
        Antivirus av(std::filesystem::path("C:\\anti-virus\\input.csv"), 1);

        while (true)
        {
            auto detections = av.ScanRunningProcesses();

            // Print detections
            for (const auto& detection : detections)
            {
                std::cout << detection.second.toPrint() << std::endl;
            }

            // Wait until next interval
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "bad input error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
}

```
