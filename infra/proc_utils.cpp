#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include "psapi.h" // GetProcessImageFileName

#include "proc_utils.h"

std::vector<infra::ProcessDescriptor> infra::getRunningProcesses()
{
    std::vector<infra::ProcessDescriptor> vecRes;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "Could not get running processes, CreateToolhelp32Snapshot failed, error" <<
            GetLastError() << std::endl;
        return {};
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        std::cout << "Could not get running processes, Process32First failed, error" <<
            GetLastError() << std::endl;
        CloseHandle(hProcessSnap);          // clean the snapshot object
        return {};
    }

    // Now walk the snapshot of processes
    do
    {
        infra::ProcessDescriptor desc;
        desc.name = pe32.szExeFile;
        desc.pid = pe32.th32ProcessID;

        // Get handle 
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe32.th32ProcessID);
        if (hProcess == NULL)
        {
            // TODO: print a Warning to log? might be protected or system proccess
            continue;
        }

        wchar_t arrImageFileName[MAX_PATH];
        DWORD pathSize = MAX_PATH;
        BOOL success = QueryFullProcessImageNameW(hProcess,0, arrImageFileName, &pathSize);
        if (success)
        {
            desc.path = std::wstring(arrImageFileName);
        }
        else
        {
            std::cout << "QueryFullProcessImageName failed, error:" << GetLastError() << std::endl;
        }

        // Closing process handle
        CloseHandle(hProcess);

        vecRes.push_back(desc);
    } while (Process32Next(hProcessSnap, &pe32));

    // Closing snapshot handle
    CloseHandle(hProcessSnap);
    
    return vecRes;
}
