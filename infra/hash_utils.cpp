#include <vector>
#include <filesystem>

#include "hash_utils.h"
#include "hash/sha256/picosha2.h"


std::vector<unsigned char> readFile(std::filesystem::path filePath)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        // TODO: Log error
        return {};
    }

    return std::vector<unsigned char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

}

std::string infra::getSha256(std::filesystem::path filePath)
{
    auto fileBuf = readFile(filePath);
    
    std::string hash_hex_str;
    picosha2::hash256_hex_string(fileBuf.cbegin(), fileBuf.cend(), hash_hex_str);


    return hash_hex_str;
}
