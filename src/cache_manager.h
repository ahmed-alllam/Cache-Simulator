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

        // statistics
        int numberOfHits = 0;
        int numberOfMisses = 0;
        int numberOfAccesses = 0;
        int hitRate = 0;
        int missRate = 0;
        int averageAccessTime = 0;

        // cache
        vector<string> instructionCache;
        vector<string> dataCache;
        
        void accessInstruction(int access);
        void accessData(int access);
    public:
        CacheManager(int cacheSize, int cacheLineSize, int cacheAccessCycles, int cacheMode, int mWay);
        void accessCache(string accessLine);
        void printStatistics();
        void printCache();
};