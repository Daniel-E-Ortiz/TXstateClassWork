/*********************************
 * Daniel Ortiz - deo15
 * Project 3 CS 3339 - Fall 2017
 *********************************/

#include "Stats.h"

Stats::Stats() {
  cycles = PIPESTAGES - 1;  // pipeline startup cost
  flushes = 0;
  bubbles = 0;
  memops = 0;
  branches = 0;
  taken = 0;
  /* PIPESTAGES = 8  [ IF1| IF2| ID |EXE1|EXE2|MEM1|MEM2| WB ]
  * rawHazards[i]  = [    |    |    |    | ++ |    |    |    ]
  -------------------            ID
  * resultReg[i]   = [    |    |    |----| 30 |    |    |    ]
  * resultStage[i] = [    |    |    |----|MEM1|    |    |    ]
  * Instr Need rd(30) in EXE1.      |--------> 1 clock from now
  *        found in EXE2, valid in MEM1, thats 1 clock from now.
  * What stage is the raw hazard in? Then when will it be valid?
  */

  /* clock moves everything down
  *  bubble moves things down from a position specified
  */
  /* ALL THE R TYPES ARE EXACTLY THE SAME!
  */
  for(int i = IF1; i < PIPESTAGES; i++) {
    rawhazards[i] = 0;
    resultReg[i] = -1;
    resultStage[i] = 0;
  }
}

void Stats::clock(PIPESTAGE stage) {
  cycles++;
  /* This method is complete
     pipeline the register tracking from provided start stage
     (ops in 'stage' thru end of pipe advance, ops in stages before 'stage'
     are frozen) */
  for(int i = WB; i > stage; i--) {
    resultReg[i] = resultReg[i-1];
    resultStage[i] = resultStage[i-1];
  }
  // inject no-op into 'stage'
  resultReg[stage] = -1;
  resultStage[stage] = 0;
}
/*           int r: register # we are using as a source.
 * PIPESTAGE stage: stage in pipeline when register will be needed.
 */
void Stats::registerSrc(int r, PIPESTAGE stage) {
  /* TODO scan for RAW hazards; if found, record and
     insert required number of bubbles */
    long int bubblies;
    for(int i = EXE1; i < WB; i++) {
      if(r == resultReg[i]){
        rawhazards[i]++;
        bubblies = (resultStage[i] - i) - (stage-ID);
        for(int j = 0; j < bubblies; j++) { bubble(); }
        break;
        }
      }
}
/*           int r: register # you are writting to.
 * PIPESTAGE stage: stage in pipeline where register is available?
 */
void Stats::registerDest(int r, PIPESTAGE stage) {
  /* TODO record destination register info */
  resultReg[ID] = r;
  resultStage[ID] = stage;
}

void Stats::flush(int count) {
  /* TODO implement flush, count == how many ops to flush */
  for(int i = 0; i < count; i++){
    flushes++;
    clock(IF1);
  }
}

int Stats::getRAWHazards(PIPESTAGE stage) {
  /* TODO return RAW hazard counts */
  return rawhazards[stage];
}

void Stats::bubble() {
  /* TODO implement bubble i.e. run flops forward of ID, inject -1 op to EXE1 */
  bubbles++;
  clock(EXE1);

}
