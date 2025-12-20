#include "Algorithm.h"
#include "IntArrayLoader.h" // TODO: Include the correct loader
#include <iostream>

namespace fs = std::filesystem;

class MergeSort : public Algorithm {
public:
    std::string name() const override { return "Merge Sort"; }
    std::filesystem::path folder() const override { return "./randInts"; }

    static bool alias(const std::string alg) {
        return
            alg == "Merge Sort" ||
            alg == "merge sort" ||
            alg == "MS" ||
            alg == "ms"
        ;
    }

    void configure() override {}

    bool loadFile(const fs::path &file) override {
        return loadIntFile(file, data, dataLength);
    }

    void run() override {
        mergeSort();
    }

    std::string results() const override {
        return result;
    }

private:
    int *data = nullptr;
    size_t dataLength = 0;
    int target = 0;
    std::string result = "";

    // TODO
    // Implement the algorithm
    inline void mergeSort() const {
        
    }
};
