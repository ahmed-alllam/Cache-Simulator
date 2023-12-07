#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class CacheManager {
    private:
        int cacheSize;
        int numberOfCacheLines;
        int cacheLineSize;
        int cacheAccessCycles;
        int cacheMode;
        int mWay;

        // statistics
        int numberOfHits = 0;
        int numberOfMisses = 0;
        int numberOfAccesses = 0;
        int hitRate = 0;
        int missRate = 0;
        int averageAccessTime = 0;
    public:
        CacheManager(int cacheSize, int cacheLineSize, int cacheAccessCycles, int cacheMode, int mWay);
        void accessMemory(int address);
        void printStatistics();
        void printCache();
};