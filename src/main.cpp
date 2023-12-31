#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "cache_manager.h"

using namespace std;

int main()
{
     cout << "Hello and Welcome to our Cache Simulator!" << endl;

     cout << "Please enter the total size of the cache in Bytes: ";
     int cacheSize;
     cin >> cacheSize;

     if ((cacheSize & (cacheSize - 1)) != 0)
     {
          cout << "Invalid cache size. Must be a power of 2." << endl;
          return 1;
     }

     cout << "Please enter the cache line size in Bytes: ";
     int cacheLineSize;
     cin >> cacheLineSize;

     if ((cacheLineSize & (cacheLineSize - 1)) != 0 || cacheLineSize >= cacheSize)
     {
          cout << "Invalid cache line size. Must be a power of 2, and less than cache size." << endl;
          return 1;
     }

     cout << "Please enter the number of cycles to access the cache: ";
     int cacheAccessCycles;
     cin >> cacheAccessCycles;

     if (cacheAccessCycles < 1 && cacheAccessCycles > 10)
     {
          cout << "Invalid number of cycles to access the cache. Must be between 1 and 10." << endl;
          return 1;
     }

     cout << "Please enter cache mode (0 for Direct Mapped, 1 for Fully Associative, 2 for m-way Set Associative): ";
     int cacheMode;
     cin >> cacheMode;

     if (cacheMode < 0 && cacheMode > 2)
     {
          cout << "Invalid cache mode. Must be 0, 1 or 2." << endl;
          return 1;
     }

     int mWay = 0;

     if (cacheMode == 2)
     {
          cout << "Please enter the m-way for set associative: ";
          cin >> mWay;
     }

     if (cacheMode == 2 && (mWay < 1 || mWay & (mWay - 1) != 0 || mWay > cacheSize / cacheLineSize))
     {
          cout << "Invalid m-way. Must be a power of 2. Must be less than or equal to cache size / cache line size." << endl;
          return 1;
     }

     cout << "Please enter the path of the file containing the memory accesses: ";
     string filePath;
     cin >> filePath;

     CacheManager cacheManager(cacheSize, cacheLineSize, cacheAccessCycles, cacheMode, mWay);

     ifstream file(filePath);

     if (!file.is_open())
     {
          cout << "Invalid file path." << endl;
          return 1;
     }

     string line;

     cout << endl
          << endl
          << endl
          << "========================================" << endl
          << endl
          << endl;

     cout << "Starting simulation..." << endl;
     cout << "Cache is empty." << endl;

     while (getline(file, line))
     {

          if (line.size() < 3)
          {
               continue;
          }

          cout << endl
               << endl
               << "========================================" << endl
               << endl;
          cacheManager.accessCache(line);
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

     cout << "Printing statistics..." << endl
          << endl;

     cacheManager.printStatistics();

     cout << endl
          << endl
          << "========================================" << endl
          << endl;

     cout << "Thank you for using our Cache Simulator!" << endl;

     return 0;
}
