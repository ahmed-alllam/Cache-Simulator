#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "cache_manager.h"

using namespace std;

int main() {
    cout << "Hello and Welcome to our Cache Simulator!" << endl;

    cout << "Please enter the total size of the cache in Bytes: ";
    int cacheSize;
    cin >> cacheSize;

    // Todo: validate all inputs

    cout << "Please enter the cache line size in Bytes: ";
    int cacheLineSize;
    cin >> cacheLineSize;

    cout << "Please enter the number of cycles to access the cache: ";
    int cacheAccessCycles;
    cin >> cacheAccessCycles;

    cout << "Please enter cache mode (0 for Direct Mapped, 1 for Fully Associative, 2 for m-way Set Associative): ";
    int cacheMode;
    cin >> cacheMode;

    int mWay = 0;

    if (cacheMode == 1) {
        cout << "Please enter the m-way for set associative: ";
        cin >> mWay;
    }

    cout << "Please enter the path of the file containing the memory accesses: ";
    string filePath;
    cin >> filePath;

    CacheManager cacheManager(cacheSize, cacheLineSize, cacheAccessCycles, cacheMode, mWay);

    ifstream file(filePath);
    string line;

    cout << endl << endl << endl << "========================================" << endl << endl << endl;

    cout << "Starting simulation..." << endl;
    cout << "Cache is empty." << endl;

    cout << "Address\t\tTag\t\tData\t\tValid" << endl; // Todo: Make sure this is the right format

    while (getline(file, line)) {
        cout << endl
             << endl
             << "========================================" << endl
             << endl;
        cacheManager.accessMemory(stoi(line)); // Todo: Make sure this is the right format
        cacheManager.printCache();
    }

    cout << endl
         << endl
         << "========================================" << endl
         << endl;

    cout << "Simulation finished." << endl;

    cout << endl
         << endl
         << "========================================" << endl
         << endl;

    cout << "Printing statistics..." << endl << endl;

    cacheManager.printStatistics();

    cout << endl
         << endl
         << "========================================" << endl
         << endl;

    cout << "Thank you for using our Cache Simulator!" << endl;

    return 0;
}