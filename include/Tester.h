#pragma once
#include <filesystem>
#include <iostream>
#include "Algorithm.h"

namespace fs = std::filesystem;

class Tester {
public:
    enum class FileSizeMode
    {
        Small,
        Medium,
        Big,
        All
    };

    static void runOnFiles(
        FileSizeMode mode,
        Algorithm *algorithm
    );

private:
    static bool startsWith(const std::string& str,
                    const std::string& prefix)
    {
        return str.size() >= prefix.size() &&
            str.compare(0, prefix.size(), prefix) == 0;
    }

    static std::string modePrefix(FileSizeMode mode)
    {
        switch (mode) {
            case FileSizeMode::Small:  return "small";
            case FileSizeMode::Medium: return "medium";
            case FileSizeMode::Big:    return "big";
            case FileSizeMode::All:    return "";
        }
        return "";
    }

    static std::vector<fs::path> selectFiles(const fs::path folder,
                                  FileSizeMode mode)
    {
        std::vector<fs::path> result;

        if (!fs::exists(folder) || !fs::is_directory(folder)) {
            return result;
        }

        const std::string prefix = modePrefix(mode);

        for (const auto& entry : fs::directory_iterator(folder)) {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".txt")
                continue;

            const std::string filename = entry.path().filename().string();

            if (mode != FileSizeMode::All) {
                if (!startsWith(filename, prefix))
                    continue;
            }

            result.push_back(entry.path());
        }

        std::sort(result.begin(), result.end());
        return result;
    }
};


