#include "testWrapper.cpp"
#include <string>
#include <iostream>
using namespace std;

void getAlgStr(string &algStr, string &modeStr) {
    cout << "Specify the Algorithm: ";
    cin >> algStr;

    cout << "Specify the Mode (Small, Medium, Big, All): ";
    cin >> modeStr;
}

int main(int argc, char* argv[]) {
    string algStr, modeStr;
    if (argc != 3) {
        getAlgStr(algStr, modeStr);
    } else {
        algStr = argv[1];
        modeStr = argv[2];
    }
    
    Test(algStr, modeStr);
}