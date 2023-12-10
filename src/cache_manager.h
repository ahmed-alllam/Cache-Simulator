#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class CacheManager {
    private:
        // configuration
        int cacheSize;
        int numberOfCacheLines;
        int cacheLineSize;
        int cacheAccessCycles;
        int cacheMode;
        int mWay;
        int memoryAccessCycles = 120;

        // statistics
        int numberOfHits = 0;
        int numberOfMisses = 0;
        int numberOfAccesses = 0;
        float hitRate = 0.0;
        float missRate = 0.0;
        float averageAccessTime = 0.0;

        // cache
        vector<string> instructionCache;
        vector<string> dataCache;
        
        void accessCacheInternal(int access, vector<string> &cache);
    public:
        CacheManager(int cacheSize, int cacheLineSize, int cacheAccessCycles, int cacheMode, int mWay);
        void accessCache(string accessLine);
        void printStatistics();
        void printCache();
};

const size_t memoryAddressSize = 24;