#include <fstream>
#include <sstream>
#include <unordered_map>
#include <filesystem> 
#include "csv_utils.h"

using ConfigurationStructure = std::unordered_map<std::string, std::vector<std::string>>;

std::unordered_map<std::string,std::vector<std::string>> infra::readCsv(std::filesystem::path filePath, int keyColumnIdx)
{
    std::ifstream file(filePath);
    std::string strLine;
    std::unordered_map<std::string, std::vector<std::string>> mapRes;
    while (std::getline(file, strLine))
    {
        std::stringstream ssLine(strLine);
        std::vector<std::string> vecLine;
        std::string strElem;
        int columnIdx = 0;
        std::string keyColumnValue;
        while (std::getline(ssLine, strElem, ','))
        {
            if (columnIdx == keyColumnIdx)
            {
                keyColumnValue = strElem;
            }
            else
            {
                vecLine.push_back(strElem);
            }

            if (!keyColumnValue.empty())
            {
                mapRes[keyColumnValue] = vecLine;
            }
            else
            {
                // TODO: Log error, bad configuration
            }


            ++columnIdx;
        }

        
    }

    return mapRes;
}
