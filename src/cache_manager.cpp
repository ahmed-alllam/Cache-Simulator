#include <iostream>
#include <bitset>
#include <cmath>

#include "cache_manager.h"

using namespace std;

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
        cout << "Accessing instruction cache..." << endl;
        cout << "Accessing address " << accessLine.substr(2) << "..." << endl;
        this->accessCacheInternal(stoi(accessLine.substr(2)), this->instructionCache);
    } else if (accessLine[0] == 'D') {
        cout << "Accessing data cache..." << endl;
        cout << "Accessing address " << accessLine.substr(2) << "..." << endl;
        this->accessCacheInternal(stoi(accessLine.substr(2)), this->dataCache);
    } else {
        cout << "Invalid access type." << endl;
    }
}

void CacheManager::accessCacheInternal(int access, vector<string> &cache) {
    string binaryAddress = bitset<memoryAddressSize>(access).to_string();

    string tag, indexBinary;
    int index;
    bool hit = false;

    switch (this->cacheMode) {
        case 0: // Direct Mapped
            indexBinary = binaryAddress.substr(memoryAddressSize - log2(this->numberOfCacheLines), log2(this->numberOfCacheLines));
            tag = binaryAddress.substr(0, memoryAddressSize - log2(this->numberOfCacheLines));
            index = stoi(indexBinary, nullptr, 2);

            if (cache[index] == tag) {
                hit = true;
            }
            break;
        case 1: // Fully Associative
            tag = binaryAddress;
            for (int i = 0; i < this->numberOfCacheLines; ++i) {
                if (cache[i] == tag) {
                    hit = true;
                    index = i;
                    break;
                }
            }
            if (!hit) {
                index = numberOfAccesses % this->numberOfCacheLines;
            }
            break;
        case 2: // m-way Set Associative
            int setIndex = stoi(binaryAddress.substr(memoryAddressSize - log2(this->numberOfCacheLines / this->mWay), log2(this->numberOfCacheLines / this->mWay)), nullptr, 2);
            tag = binaryAddress.substr(0, memoryAddressSize - log2(this->numberOfCacheLines));
            for (int i = setIndex * this->mWay; i < (setIndex + 1) * this->mWay; ++i) {
                if (cache[i] == tag) {
                    hit = true;
                    index = i;
                    break;
                }
            }
            if (!hit) {
                index = setIndex * this->mWay + (numberOfAccesses % this->mWay);
            }
            break;
    }

    if (hit) {
        numberOfHits++;
    } else {
        numberOfMisses++;
        cache[index] = binaryAddress;
    }

    numberOfAccesses++;

    cout << "Accessing address " << access << "..." << endl;
    cout << "Tag: " << tag << endl;
    cout << "Index: " << index << endl;
    cout << "Hit: " << (hit ? "Yes" : "No") << endl;
}

void CacheManager::printStatistics() {
    hitRate = numberOfHits * 100 / numberOfAccesses;
    missRate = numberOfMisses * 100 / numberOfAccesses;
    averageAccessTime = (numberOfHits * cacheAccessCycles + numberOfMisses * (cacheAccessCycles + memoryAccessCycles)) / numberOfAccesses;

    cout << "Number of hits: " << numberOfHits << endl;
    cout << "Number of misses: " << numberOfMisses << endl;
    cout << "Number of accesses: " << numberOfAccesses << endl;
    cout << "Hit rate: " << hitRate << "%" << endl;
    cout << "Miss rate: " << missRate << "%" << endl;
    cout << "Average access time: " << averageAccessTime << " cycles" << endl;
}

void CacheManager::printCache() {
    cout << "Direct Mapped Cache Contents:" << endl;
    for (int i = 0; i < this->numberOfCacheLines; ++i) {
        cout << "Cache Line " << i << ": ";
        // Assuming that an empty string in the cache vector indicates an empty line
        if (this->instructionCache[i].empty()) {
            cout << "empty";
        } else {
            cout << "Tag: " << this->instructionCache[i];
        }
        cout << endl;
    }
   
}
