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
    char type = accessLine[0];
    int address = stoi(accessLine.substr(2));

    if (type == 'I') {
        cout << "Accessing instruction cache with address: " << address << "..." << endl;
        this->accessCacheInternal(address, this->instructionCache);
    } else if (type == 'D') {
        cout << "Accessing data cache with address: " << address << "..." << endl;
        this->accessCacheInternal(address, this->dataCache);
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
        case 0: {
            int indexBits = log2(this->numberOfCacheLines);
            indexBinary = binaryAddress.substr(memoryAddressSize - indexBits, indexBits);
            tag = binaryAddress.substr(0, memoryAddressSize - indexBits);
            index = stoi(indexBinary, nullptr, 2);

            if (!cache[index].empty() && cache[index].substr(0, memoryAddressSize - indexBits) == tag) {
                hit = true;
            }
            break;
        }
        case 1: {
            tag = binaryAddress;
            for (int i = 0; i < this->numberOfCacheLines; ++i) {
                if (!cache[i].empty() && cache[i] == tag) {
                    hit = true;
                    index = i;
                    break;
                }
            }
            if (!hit) {
                index = numberOfAccesses % this->numberOfCacheLines;
            }
            break;
        }
        case 2: {
            int setBits = log2(this->numberOfCacheLines / this->mWay);
            int setIndex = stoi(binaryAddress.substr(memoryAddressSize - setBits, setBits), nullptr, 2);
            tag = binaryAddress.substr(0, memoryAddressSize - setBits);
            for (int i = setIndex * this->mWay; i < (setIndex + 1) * this->mWay; ++i) {
                if (!cache[i].empty() && cache[i].substr(0, memoryAddressSize - setBits) == tag) {
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
    }

    if (hit) {
        numberOfHits++;
    } else {
        numberOfMisses++;
        cache[index] = binaryAddress;
    }

    numberOfAccesses++;

    cout << "Tag: " << tag << endl;
    cout << "Index: " << index << endl;
    cout << "Hit: " << (hit ? "Yes" : "No") << endl;
}

void CacheManager::printStatistics() {
    hitRate = (float) numberOfHits / numberOfAccesses * 100;
    missRate = (float) numberOfMisses / numberOfAccesses * 100;
    averageAccessTime = (static_cast<float>(numberOfHits) * cacheAccessCycles + static_cast<float>(numberOfMisses) * (cacheAccessCycles + memoryAccessCycles)) / static_cast<float>(numberOfAccesses);


    cout << "Number of hits: " << numberOfHits << endl;
    cout << "Number of misses: " << numberOfMisses << endl;
    cout << "Number of accesses: " << numberOfAccesses << endl;
    cout << "Hit rate: " << hitRate << "%" << endl;
    cout << "Miss rate: " << missRate << "%" << endl;
    cout << "Average access time: " << averageAccessTime << " cycles" << endl;
}

void CacheManager::printCache() {
    cout << endl << endl << "Printing instruction cache..." << endl << endl;

    for (int i = 0; i < this->numberOfCacheLines; ++i) {
        cout << "Cache line " << i << ": " << this->instructionCache[i] << endl;
    }


    cout << endl << endl << "==============================" << endl << endl;

    cout << "Printing data cache..." << endl << endl;

    for (int i = 0; i < this->numberOfCacheLines; ++i) {
        cout << "Cache line " << i << ": " << this->dataCache[i] << endl;
    }

    cout << endl << endl << "==============================" << endl << endl;
   
}
