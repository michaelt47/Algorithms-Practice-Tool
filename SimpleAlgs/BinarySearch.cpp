#include "Algorithm.h"
#include "IntArrayLoader.h"
#include <iostream>

namespace fs = std::filesystem;

class BinarySearch : public Algorithm {
public:
    std::string name() const override { return "Binary Search"; }
    std::filesystem::path folder() const override { return "./randSortedInts"; }

    ~BinarySearch() override {
        delete[] data;
    }

    static bool alias(const std::string alg) {
        return alg == "Binary Search" 
            || alg == "binary search"
            || alg == "bs"
            || alg == "BS"
        ;
    }

    void configure() override {
        std::cout << "Target: ";
        std::cin >> target;
    }

    bool loadFile(const fs::path &file) override {
        return loadIntFile(file, data, dataLength);
    }

    void run() override {
        binarySearch();
    }

    std::string results() const override {
        return result;
    }

private:
    int *data = nullptr;
    size_t dataLength = 0;
    int target = 0;
    std::string result = "";

    inline void binarySearch() {
        if (dataLength == 0) {
            // result = "Could not find target\n";
            return;
        }

        size_t low = 0;
        size_t high = dataLength;

        while (low < high) {
            size_t mid = low + (high - low) / 2;
            if (data[mid] == target) {
                // result = "Successfully found target " + std::to_string(target) + "\n";
                return;
            } else if (data[mid] < target) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        // result = "Could not find target " + std::to_string(target) + "\n";
    }
};
