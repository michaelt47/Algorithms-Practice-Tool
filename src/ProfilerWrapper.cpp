#include "Profiler.h"
#include "Algorithm.h"
#include "Summation.cpp"
#include "BinarySearch.cpp"

using namespace std;

void getAlgorithm(const string &algStr, const string &modeStr, 
                Algorithm *&algorithm, Profiler::FileSizeMode &testMode) {
    if (BinarySearch::alias(algStr)) {
        algorithm = new BinarySearch();
    } else if (Summation::alias(algStr)) {
        algorithm = new Summation();
    } else {
        cout << "Invalid algorithm\n";
        exit(0);
    }

    if (modeStr == "Small" || modeStr == "small") {
        testMode = Profiler::FileSizeMode::Small;
    } else if (modeStr == "Medium" || modeStr == "medium") {
        testMode = Profiler::FileSizeMode::Medium;
    } else if (modeStr == "Big" || modeStr == "big") {
        testMode = Profiler::FileSizeMode::Big;
    } else if (modeStr == "All" || modeStr == "all") {
        testMode = Profiler::FileSizeMode::All;
    } else {
        cout << "Invalid mode, defaulting to small\n";
        testMode = Profiler::FileSizeMode::Small;
    }
}

void Test(const string &algStr, const string &modeStr) {
    Profiler::FileSizeMode testMode;
    Algorithm *algorithm;

    getAlgorithm(algStr, modeStr, algorithm, testMode);

    if (algorithm) {
        Profiler::runOnFiles(testMode, algorithm);
        delete algorithm;
    }
}