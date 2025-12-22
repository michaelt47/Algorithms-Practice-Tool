#include "Algorithm.h"
#include "IntArrayLoader.h"
#include <iostream>

namespace fs = std::filesystem;

class MergeSort : public Algorithm {
public:
    ~MergeSort() {
        delete[] data;
        delete[] temp;
    }

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
        result = "";
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
    int *temp = nullptr;
    size_t dataLength = 0;
    std::string result = "";

    void merge(
        int *out, 
        int *left, int *right, 
        int leftLen, int rightLen
    ) {
        int leftIndex = 0;
        int rightIndex = 0;
        while (leftIndex < leftLen && rightIndex < rightLen) {
            if (left[leftIndex] < right[rightIndex]) {
                out[leftIndex + rightIndex] = left[leftIndex];
                leftIndex++;
            } else {
                out[leftIndex + rightIndex] = right[rightIndex];
                rightIndex++;
            }
        }

        while (leftIndex < leftLen) {
            out[leftIndex + rightIndex] = left[leftIndex];
            leftIndex++;
        }

        while (rightIndex < rightLen) {
            out[leftIndex + rightIndex] = right[rightIndex];
            rightIndex++;
        }
    }

    void mergeSortRecurse(int *arr, int len) {
        if (len <= 1) return;

        int half = len / 2;
        
        mergeSortRecurse(arr, half);
        mergeSortRecurse(&arr[half], len - half);

        for (int i = 0; i < len; i++) {
            temp[i] = arr[i];
        }
        merge(arr, temp, &temp[half], half, len - half);
    }

    inline void mergeSort() {
        if (temp) delete[] temp;
        temp = new int[dataLength];
        mergeSortRecurse(data, dataLength);
        
        // for (int i = 0; i < dataLength; i++) {
        //     result += std::to_string(data[i]) + "\n";
        // }
    }
};
