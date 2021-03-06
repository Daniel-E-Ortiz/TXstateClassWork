#ifndef __CACHE_STATS_H
#define __CACHE_STATS_H

#include <cstdint>
#include "Debug.h"
using namespace std;

#ifndef CACHE_EN
#define CACHE_EN 1
#endif

#ifndef BLOCKSIZE
#define BLOCKSIZE 32
#endif

#ifndef SETS
#define SETS 8
#endif

#ifndef WAYS
#define WAYS 4
#endif

#ifndef LOOKUP_LATENCY
#define LOOKUP_LATENCY 0
#endif

#ifndef READ_LATENCY
#define READ_LATENCY 30
#endif

#ifndef WRITE_LATENCY
#define WRITE_LATENCY 10
#endif

enum ACCESS_TYPE { LOAD, STORE };

class CacheStats {
  private:
    /* Add member variables to allow you to model the cache behavior
       example for valid and round robin is provided, you will likely
	   need dirty and tags as well	   */
    bool valid[SETS][WAYS];
    /* dirty */
    bool dirty[SETS][WAYS];
    /* tags which will hold address data so not bool type...*/
    uint32_t tags[SETS][WAYS];
    int roundRobin[SETS];

    int loads;
    int stores;
    int load_misses;
    int store_misses;
    int writebacks;

  public:
    CacheStats();
    int access(uint32_t, ACCESS_TYPE);
    void printFinalStats();

};

#endif
