#include "Algorithm.h"
#include "IntArrayLoader.h"
#include <iostream>

namespace fs = std::filesystem;

class Summation : public Algorithm {
public:
    std::string name() const override { return "Summation"; }
    std::filesystem::path folder() const override { return "./randInts"; }

    ~Summation() override {
        delete[] data;
    }

    static bool alias(const std::string alg) {
        return alg == "Sum" 
            || alg == "sum"
            || alg == "Summation"
            || alg == "summation"
        ;
    }

    void configure() override {}

    bool loadFile(const fs::path &file) override {
        return loadIntFile(file, data, dataLength);
    }

    void run() override {
        summation();
    }

    std::string results() const override {
        return result;
    }

private:
    int *data = nullptr;
    size_t dataLength = 0;
    std::string result = "";

    inline void summation() {
        long long sum = 0;
        for (int i = 0; i < dataLength; i++) {
            sum += data[i];
        }
        // result = "Successfully calculated sum of: " + std::to_string(sum) + "\n";
    }
};
