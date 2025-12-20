#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

inline bool loadIntFile(
    const fs::path& filePath,
    int*& outArray,
    size_t& outLength
)
{
    outArray = nullptr;
    outLength = 0;
    
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << filePath << "\n";
        return false;
    }

    std::vector<int> values;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        long long value = 0;

        try
        {
            value = std::stoull(line);
        }
        catch (...)
        {
            std::cerr << "Invalid integer in " << filePath << "\n";
            return false;
        }

        if (value > std::numeric_limits<int>::max())
        {
            std::cerr << "Value out of range in " << filePath << "\n";
            return false;
        }

        values.push_back(static_cast<int>(value));
    }

    outLength = values.size();
    outArray = new int[outLength];

    for (size_t i = 0; i < outLength; ++i)
        outArray[i] = values[i];

    return true;
}