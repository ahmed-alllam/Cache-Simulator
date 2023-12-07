#include "cache_manager.h"

CacheManager::CacheManager(int cacheSize, int cacheLineSize, int cacheAccessCycles, int cacheMode, int mWay) {
    this->cacheSize = cacheSize;
    this->cacheLineSize = cacheLineSize;
    this->numberOfCacheLines = this->cacheSize / this->cacheLineSize;
    this->cacheAccessCycles = cacheAccessCycles;
    this->cacheMode = cacheMode;
    this->mWay = mWay;
}
