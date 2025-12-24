#include "Algorithm.h"
#include "GraphLoader.h"
#include <iostream>
#include <queue>

namespace fs = std::filesystem;

class BreadthFirstSearch : public Algorithm {
public:
    ~BreadthFirstSearch() {}

    std::string name() const override { return "Breadth First Search"; }
    std::filesystem::path folder() const override { return folderName; }

    static bool alias(const std::string alg) {
        return alg == "Breadth First Search"
            || alg == "breadth first search"
            || alg == "BFS"
            || alg == "bfs"
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
            breadthFirstSearchMatrix();
        } else {
            breadthFirstSearchList();
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

    void breadthFirstSearchList() {
        std::vector<bool> visited(adjList.size(), false);
        std::queue<int> q;

        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            for (auto &neighbor : adjList[vertex]) {
                if (!visited[neighbor.to]) {
                    visited[neighbor.to] = true;
                    q.push(neighbor.to);
                }
            }
        }
    }

    void breadthFirstSearchMatrix() {
        std::vector<bool> visited(adjMatrix.size(), false);
        std::queue<int> q;

        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            
            for (int i = 0; i < adjMatrix[vertex].size(); i++) {
                if (adjMatrix[vertex][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
};
