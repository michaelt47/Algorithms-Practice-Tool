#include "Tester.h"
#include "Algorithm.h"
#include "Summation.cpp"
#include "BinarySearch.cpp"

using namespace std;

void getAlgorithm(const string &algStr, const string &modeStr, 
                Algorithm *&algorithm, Tester::FileSizeMode &testMode) {
    if (BinarySearch::alias(algStr)) {
        algorithm = new BinarySearch();
    } else if (Summation::alias(algStr)) {
        algorithm = new Summation();
    } else {
        cout << "Invalid algorithm\n";
        exit(0);
    }

    if (modeStr == "Small" || modeStr == "small") {
        testMode = Tester::FileSizeMode::Small;
    } else if (modeStr == "Medium" || modeStr == "medium") {
        testMode = Tester::FileSizeMode::Medium;
    } else if (modeStr == "Big" || modeStr == "big") {
        testMode = Tester::FileSizeMode::Big;
    } else if (modeStr == "All" || modeStr == "all") {
        testMode = Tester::FileSizeMode::All;
    } else {
        cout << "Invalid mode, defaulting to small\n";
        testMode = Tester::FileSizeMode::Small;
    }
}

void Test(const string &algStr, const string &modeStr) {
    Tester::FileSizeMode testMode;
    Algorithm *algorithm;

    getAlgorithm(algStr, modeStr, algorithm, testMode);

    if (algorithm) {
        Tester::runOnFiles(testMode, algorithm);
        delete algorithm;
    }
}