#include "cache_manager.h"

CacheManager::CacheManager(int cacheSize, int cacheLineSize, int cacheAccessCycles, int cacheMode, int mWay) {
    this->cacheSize = cacheSize;
    this->cacheLineSize = cacheLineSize;
    this->numberOfCacheLines = this->cacheSize / this->cacheLineSize;
    this->cacheAccessCycles = cacheAccessCycles;
    this->cacheMode = cacheMode;
    this->mWay = mWay;

    this->instructionCache = vector<string>(this->numberOfCacheLines);
    this->dataCache = vector<string>(this->numberOfCacheLines);
}

void CacheManager::accessCache(string accessLine) {
    if (accessLine[0] == 'I') {
        this->accessInstruction(stoi(accessLine.substr(2)));
    } else if (accessLine[0] == 'D') {
        this->accessData(stoi(accessLine.substr(2)));
    } else {
        cout << "Invalid access type." << endl;
    }
}

void CacheManager::accessInstruction(int access) {

}

void CacheManager::accessData(int access) {

}
