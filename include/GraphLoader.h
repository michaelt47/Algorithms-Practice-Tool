#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include "graphs.h"

namespace fs = std::filesystem;

inline bool loadGraphAdjList(
    const fs::path& filePath,
    std::vector<std::vector<AdjListEdge>>& outAdjList,
    bool& outDirected,
    std::vector<int>* outWeights = nullptr
) {
    outAdjList.clear();
    if (outWeights)
        outWeights->clear();

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << filePath << "\n";
        return false;
    }

    // --- Read header ---
    size_t numNodes = 0;
    size_t numEdges = 0;
    int directedFlag = 0;

    if (!(file >> numNodes >> numEdges >> directedFlag))
    {
        std::cerr << "Invalid graph header in " << filePath << "\n";
        return false;
    }

    outDirected = (directedFlag != 0);
    outAdjList.resize(numNodes);

    // --- Read edges ---
    size_t edgesRead = 0;
    std::string line;
    std::getline(file, line);

    while (edgesRead < numEdges && std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);

        long long u, v;
        if (!(ss >> u >> v))
        {
            std::cerr << "Invalid edge format in " << filePath << "\n";
            return false;
        }

        if (u < 0 || v < 0 || u >= (long long)numNodes || v >= (long long)numNodes)
        {
            std::cerr << "Node index out of range in " << filePath << "\n";
            return false;
        }

        int weightIndex = -1;

        if (outWeights)
        {
            long long w;
            if (!(ss >> w))
            {
                std::cerr << "Expected weight but none found in " << filePath << "\n";
                return false;
            }

            if (w < std::numeric_limits<int>::min() ||
                w > std::numeric_limits<int>::max())
            {
                std::cerr << "Weight out of range in " << filePath << "\n";
                return false;
            }

            weightIndex = static_cast<int>(outWeights->size());
            outWeights->push_back(static_cast<int>(w));
        }

        outAdjList[u].push_back({ static_cast<int>(v), weightIndex });

        if (!outDirected)
        {
            outAdjList[v].push_back({ static_cast<int>(u), weightIndex });
        }

        ++edgesRead;
    }

    if (edgesRead != numEdges)
    {
        std::cerr << "Edge count mismatch in " << filePath << "\n";
        return false;
    }

    return true;
}

inline bool loadGraphAdjMatrix(
    const fs::path& filePath,
    std::vector<std::vector<int>>& outMatrix,
    bool& outDirected
) {
    outMatrix.clear();

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << filePath << "\n";
        return false;
    }

    // --- Read header ---
    size_t numNodes = 0;
    size_t numEdges = 0;
    int directedFlag = 0;

    if (!(file >> numNodes >> numEdges >> directedFlag))
    {
        std::cerr << "Invalid graph header in " << filePath << "\n";
        return false;
    }

    outDirected = (directedFlag != 0);

    // Initialize matrix
    outMatrix.assign(numNodes, std::vector<int>(numNodes, 0));

    // Consume remainder of header line
    std::string line;
    std::getline(file, line);

    // --- Read edges ---
    size_t edgesRead = 0;

    while (edgesRead < numEdges && std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);

        long long u, v;
        if (!(ss >> u >> v))
        {
            std::cerr << "Invalid edge format in " << filePath << "\n";
            return false;
        }

        if (u < 0 || v < 0 ||
            u >= static_cast<long long>(numNodes) ||
            v >= static_cast<long long>(numNodes))
        {
            std::cerr << "Node index out of range in " << filePath << "\n";
            return false;
        }

        int weight = 1; // default for unweighted edge

        // Optional weight
        if (ss >> weight)
        {
            // Weight read successfully (can be negative)
            if (weight < std::numeric_limits<int>::min() ||
                weight > std::numeric_limits<int>::max())
            {
                std::cerr << "Weight out of range in " << filePath << "\n";
                return false;
            }
        }

        outMatrix[u][v] = weight;

        if (!outDirected)
        {
            outMatrix[v][u] = weight;
        }

        ++edgesRead;
    }

    if (edgesRead != numEdges)
    {
        std::cerr << "Edge count mismatch in " << filePath << "\n";
        return false;
    }

    return true;
}