#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "CacheStats.h"
using namespace std;

CacheStats::CacheStats() {
  cout << "Cache Config: ";
  if(!CACHE_EN) {
    cout << "cache disabled" << endl;
  } else {
    cout << (SETS * WAYS * BLOCKSIZE) << " B (";
    cout << BLOCKSIZE << " bytes/block, " << SETS << " sets, " << WAYS << " ways)" << endl;
    cout << "  Latencies: Lookup = " << LOOKUP_LATENCY << " cycles, ";
    cout << "Read = " << READ_LATENCY << " cycles, ";
    cout << "Write = " << WRITE_LATENCY << " cycles" << endl;
  }

  loads = 0;
  stores = 0;
  load_misses = 0;
  store_misses = 0;
  writebacks = 0;

  /* TODO: your code here - initialize other variables */
  for(int i = 0; i < SETS; ++i){
    roundRobin[i] = 0;
    for(int j = 0; j < WAYS; ++j){
      tags[i][j] = 0;
      valid[i][j] = false;
      dirty[i][j] = false;
    }
  }
}

int CacheStats::access(uint32_t addr, ACCESS_TYPE type) {
  if(!CACHE_EN) { // no cache
    return (type == LOAD) ? READ_LATENCY : WRITE_LATENCY;
  }
  /* TODO: your code here
     calculate data needed from addr
     figure out if hit or miss and update accordingly
     if miss and you are filling, simulate writeback
     remember to keep all the statistics too       	 */
  uint32_t index = (addr >> 5) & 7;
  uint32_t tag = addr >> 8;
  uint32_t way = roundRobin[index];
  int total = LOOKUP_LATENCY;
  // check if tag exists, if so then this is a Hit
///*
  if(type == LOAD){
    loads++;
  }
  if(type == STORE){
    stores++;
  }
  for(int j = 0; j < WAYS; j++){
    if(valid[index][j] == true && tags[index][j] == tag){
      if(type == STORE){
        dirty[index][j] = true;
      }
      return LOOKUP_LATENCY;
    }
  }
  // tag did not exist, what now?
  if(type == LOAD){
    load_misses++;
  }
  if(type == STORE){
    store_misses++;
  }
    tags[index][way] = tag;
    valid[index][way] = true;
  if(dirty[index][way] == true){
    writebacks++;
    total = (READ_LATENCY + WRITE_LATENCY);
  }
  if(type == LOAD){
    dirty[index][way] = false;
  }
  if(type == STORE){
    dirty[index][way] = true;
  }
  roundRobin[index] = (roundRobin[index] + 1) % WAYS;
  return (total == LOOKUP_LATENCY) ? READ_LATENCY : total;
}

void CacheStats::printFinalStats() {
  /* TODO: your code here to drain the cache of writebacks */
  for(int i = 0; i < SETS; ++i){
    for(int j = 0; j < WAYS; ++j){
      if(dirty[i][j] == true){
        writebacks++;
      }
    }
    roundRobin[i] = 0;
  }
  int accesses = loads + stores;
  int misses = load_misses + store_misses;
  cout << "Accesses: " << accesses << endl;
  cout << "  Loads: " << loads << endl;
  cout << "  Stores: " << stores << endl;
  cout << "Misses: " << misses << endl;
  cout << "  Load misses: " << load_misses << endl;
  cout << "  Store misses: " << store_misses << endl;
  cout << "Writebacks: " << writebacks << endl;
  cout << "Hit Ratio: " << fixed << setprecision(1) << 100.0 * (accesses - misses) / accesses;
  cout << "%" << endl;
}
