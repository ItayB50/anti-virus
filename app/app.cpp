// app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <map>
#include "../infra/infra.h"
#include "../anti-virus/antivirus.h"


int main()
{
    std::cout << "Hello World!\n";

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
        std::cout << "Unknwn error: " << e.what() << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
