#include "Algorithm.h"
#include "IntArrayLoader.h" // TODO: Include the correct loader
#include <iostream>

namespace fs = std::filesystem;

// TODO
// Change class name to the algorithm name
class AlgorithmName : public Algorithm {
public:
    // TODO
    // Free any heap memory used
    ~AlgorithmName() {
        delete[] data;
    }

    // TODO
    // Update Algorithm Name
    std::string name() const override { return "Algorithm Name"; }
    // TODO
    // Change input folder
    std::filesystem::path folder() const override { return "./inputFolder"; }

    // TODO
    // Check user input and compare to aliases of the algorithm
    static bool alias(const std::string alg) {}

    // TODO
    // Get any custom user input for the algorithm
    void configure() override {}

    // TODO
    // Use the correct loader to load the input data
    bool loadFile(const fs::path &file) override {
        result = "";
        return loadIntFile(file, data, dataLength);
    }

    // Call the algorithm here
    void run() override {
        algorithm();
    }

    // TODO
    // Write out a results string in the algorithm
    std::string results() const override {
        return result;
    }

private:
    // TODO
    // Include whatever data is needed
    int *data = nullptr;
    size_t dataLength = 0;
    int target = 0;
    std::string result = "";

    // TODO
    // Implement the algorithm
    inline void algorithm() {

    }
};
