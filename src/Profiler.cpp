#include "Profiler.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void Profiler::runOnFiles(
    FileSizeMode mode,
    Algorithm *algorithm)
{
    algorithm->configure();
    for (const fs::path &file : selectFiles(algorithm->folder(), mode)) {
        if (!algorithm->loadFile(file)) continue;

        auto start = std::chrono::high_resolution_clock::now();
        algorithm->run();
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::string results = algorithm->results();

        std::string buffer =
            algorithm->name() + " took " +
            std::to_string(elapsed.count()) +
            " ms to run on " + file.string() + "\n";
        
        buffer += results;

        std::cout << buffer;
        
    }
}