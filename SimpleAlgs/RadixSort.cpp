#include "Algorithm.h"
#include "IntArrayLoader.h" 
#include <iostream>

namespace fs = std::filesystem;

class RadixSort : public Algorithm {
public:
    ~RadixSort() {
        delete[] data;
    }

    std::string name() const override { return "Radix Sort"; }
    std::filesystem::path folder() const override { return "./randInts"; }

    static bool alias(const std::string alg) {
        return alg == "Radix Sort"
            || alg == "radix sort"
            || alg == "RS"
            || alg == "rs"
        ;
    }

    void configure() override {}

    bool loadFile(const fs::path &file) override {
        result = "";
        return loadIntFile(file, data, dataLength);
    }

    void run() override {
        radixSort();
    }

    std::string results() const override {
        return result;
    }

private:
    int *data = nullptr;
    size_t dataLength = 0;
    std::string result = "";

    void countingSort(int exp) {
        int temp[dataLength];
        int count[10] = {0};

        for (int i = 0; i < dataLength; i++) {
            count[(data[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = dataLength - 1; i >= 0; i--) {
            temp[count[(data[i] / exp) % 10] - 1] = data[i];
            count[(data[i] / exp) % 10]--;
        }

        for (int i = 0; i < dataLength; i++) {
            data[i] = temp[i];
        }
    }

    inline void radixSort() {
        int max = INT_MIN;
        for (int i = 0; i < dataLength; i++) {
            if (data[i] > max) max = data[i];
        }

        int exp = 1;
        while (max / exp >= 1) {
            countingSort(exp);
            exp *= 10;
        }

        // for (int i = 0; i < dataLength; i++) {
        //     result += std::to_string(data[i]) + "\n";
        // }
    }
};
