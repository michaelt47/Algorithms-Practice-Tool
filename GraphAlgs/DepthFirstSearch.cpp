#include "Algorithm.h"
#include "GraphLoader.h"
#include <iostream>

namespace fs = std::filesystem;

class DepthFirstSearch : public Algorithm {
public:
    ~DepthFirstSearch() {}

    std::string name() const override { return "Depth First Search"; }
    std::filesystem::path folder() const override { return folderName; }

    static bool alias(const std::string alg) {
        return alg == "Depth First Search"
            || alg == "depth first search"
            || alg == "DFS"
            || alg == "dfs"
        ;
    }

    void configure() override {
        std::cout << "Specify the folder with the graphs: ";
        std::string input;
        std::cin >> input;
        if (input != ".") {
            folderName = input;
        }
    }

    bool loadFile(const fs::path &file) override {
        result = "";
        bool directed;
        int numVertices, numEdges, directedFlag;
        std::string firstLine;
        std::ifstream inputFile(file);
        if (!inputFile.is_open()) return false;
        if (!(inputFile >> numVertices >> numEdges >> directedFlag)) return false;

        inputFile.close();

        float density = (float)(numEdges) / (float)(numVertices * (numVertices - 1));
        if (directedFlag == 0) density *= 2.f;

        if (density >= 0.5f) {
            storageType = MATRIX;
            return loadGraphAdjMatrix(file, adjMatrix, directed);
        } else {
            storageType = LIST;
            return loadGraphAdjList(file, adjList, directed);
        }

    }

    void run() override {
        if (storageType == MATRIX) {
            depthFirstSearchMatrix();
        } else {
            depthFirstSearchList();
        }
    }

    std::string results() const override {
        return result;
    }

private:
    std::vector<std::vector<AdjListEdge>> adjList;
    std::vector<std::vector<int>> adjMatrix;
    std::string result = "";
    std::string folderName = "./randGraphs/directed/weighted/negative/cyclic/";

    enum StorageType {
        LIST,
        MATRIX
    };

    StorageType storageType;

    void depthFirstSearchList() {
        std::vector<bool> visited(adjList.size(), false);
        std::vector<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            if (visited[vertex]) continue;
            visited[vertex] = true;
            for (auto &neighbor : adjList[vertex]) {
                if (!visited[neighbor.to])
                    stack.push_back(neighbor.to);
                }
        }
    }

    void depthFirstSearchMatrix() {
        std::vector<bool> visited(adjMatrix.size(), false);
        std::vector<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int vertex = stack.back();
            if (visited[vertex]) continue;
            visited[vertex] = true;
            stack.pop_back();
            if (visited[vertex]) continue;
            for (int i = 0; i < adjMatrix[vertex].size(); i++) {
                if (adjMatrix[vertex][i] != 0 && (!visited[i])) {
                    stack.push_back(i);
                }
            }
        }
    }
};
