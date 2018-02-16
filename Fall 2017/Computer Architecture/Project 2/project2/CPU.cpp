/******************************
 * Daniel Ortiz (deo15)
 * CS 3339 - 002 - Fall 2017
 * Project 2
 ******************************/
#include "CPU.h"

const string CPU::regNames[] = {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3",
                                "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
                                "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
                                "$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

CPU::CPU(uint32_t pc, Memory &iMem, Memory &dMem) : pc(pc), iMem(iMem), dMem(dMem) {
  for(int i = 0; i < NREGS; i++) {
    regFile[i] = 0;
  }
  hi = 0;
  lo = 0;
  regFile[28] = 0x10008000; // gp
  regFile[29] = 0x10000000 + dMem.getSize(); // sp

  instructions = 0;
  stop = false;
}

void CPU::run() {
  while(!stop) {
    instructions++;

    fetch();
    decode();
    execute();
    mem();
    writeback();

    D(printRegFile());
  }
}

void CPU::fetch() {
  instr = iMem.loadWord(pc);
  pc = pc + 4;
}

//////////////////////////////////////////
// ALL YOUR CHANGES GO IN THIS FUNCTION //
//////////////////////////////////////////
void CPU::decode() {
  uint32_t opcode;      // opcode field
  uint32_t rs, rt, rd;  // register specifiers
  uint32_t shamt;       // shift amount (R-type)
  uint32_t funct;       // funct field (R-type)
  uint32_t uimm;        // unsigned version of immediate (I-type)
  int32_t simm;         // signed version of immediate (I-type)
  uint32_t addr;        // jump address offset field (J-type)

  opcode = (instr >> 26);
  rs = (instr >> 21) & 0x1F;
  rt = (instr >> 16) & 0x1F;
  rd = (instr >> 11) & 0x1F;
  shamt = (instr >> 6) & 0x1F;
  funct = (instr & 0x3F);
  uimm = (instr & 0xFFFF);
  simm = ((signed)uimm << 16) >> 16;
  addr = (instr & 0x3FFFFFF);

  // Hint: you probably want to give all the control signals some "safe"
  // default value here, and then override their values as necessary in each
  // case statement below!
  /*bool*/ opIsLoad = opIsStore = opIsMultDiv = false;
  /*ALU_OP*/ aluOp = ADD;
  /*bool*/ writeDest = false;
  /*int*/ destReg = 0;
  /*uint32_t*/ aluSrc1 = aluSrc2 = 0;
  /*uint32_t*/ storeData = 0;

  D(cout << "  " << hex << setw(8) << pc - 4 << ": ");
  switch(opcode) {
    case 0x00:
      switch(funct) {
        case 0x00: D(cout << "sll " << regNames[rd] << ", " << regNames[rs] << ", " << dec << shamt);
                   aluOp = SHF_L;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = shamt;
                   writeDest = true;
                   destReg = rd;
                   break;
        case 0x03: D(cout << "sra " << regNames[rd] << ", " << regNames[rs] << ", " << dec << shamt);
                   aluOp = SHF_R;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = shamt;
                   writeDest = true;
                   destReg = rd;
                   break;
        case 0x08: D(cout << "jr " << regNames[rs]);
                   aluOp = ADD;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = regFile[REG_ZERO];
                   pc = regFile[rs];
                   break;
        case 0x10: D(cout << "mfhi " << regNames[rd]);
                   aluOp = ADD;
                   aluSrc1 = hi;
                   aluSrc2 = regFile[REG_ZERO];
                   writeDest = true;
                   destReg = rd;
                   break;
        case 0x12: D(cout << "mflo " << regNames[rd]);
                   aluOp = ADD;
                   aluSrc1 = lo;
                   aluSrc2 = regFile[REG_ZERO];
                   writeDest = true;
                   destReg = rd;
                   break;
        case 0x18: D(cout << "mult " << regNames[rs] << ", " << regNames[rt]);
                   aluOp = MUL;
                   opIsMultDiv = true;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = regFile[rt];
                   break;
        case 0x1a: D(cout << "div " << regNames[rs] << ", " << regNames[rt]);
                   aluOp = DIV;
                   opIsMultDiv = true;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = regFile[rt];
                   break;
        case 0x21: D(cout << "addu " << regNames[rd] << ", " << regNames[rs] << ", " << regNames[rt]);
                   aluOp = ADD;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = regFile[rt];
                   writeDest = true;
                   destReg = rd;
                   break;
        case 0x23: D(cout << "subu " << regNames[rd] << ", " << regNames[rs] << ", " << regNames[rt]);
                   aluOp = ADD;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = ((regFile[rt] xor 0xffffffff) + 1);
                   writeDest = true;
                   destReg = rd;
                   break;
        case 0x2a: D(cout << "slt " << regNames[rd] << ", " << regNames[rs] << ", " << regNames[rt]);
                   aluOp = CMP_LT;
                   aluSrc1 = regFile[rs];
                   aluSrc2 = regFile[rt];
                   writeDest = true;
                   destReg = rd;
                   break;
        default: cerr << "unimplemented instruction: pc = 0x" << hex << pc - 4 << endl;
      }
      break;
    case 0x02: D(cout << "j " << hex << ((pc & 0xf0000000) | addr << 2)); // P1: pc + 4
               pc = (pc & 0xf0000000) | addr << 2;
               break;
    case 0x03: D(cout << "jal " << hex << ((pc & 0xf0000000) | addr << 2)); // P1: pc + 4
               writeDest = true; destReg = REG_RA; // writes PC+4 to $ra
               aluOp = ADD; // ALU should pass pc thru unchanged
               aluSrc1 = pc;
               aluSrc2 = regFile[REG_ZERO]; // always reads zero
               pc = (pc & 0xf0000000) | addr << 2;
               break;
    case 0x04: D(cout << "beq " << regNames[rs] << ", " << regNames[rt] << ", " << pc + (simm << 2));
               if(!(regFile[rs] xor regFile[rt])){
                  pc = pc + (simm << 2);
               }
               break;
    case 0x05: D(cout << "bne " << regNames[rs] << ", " << regNames[rt] << ", " << pc + (simm << 2));
               if((regFile[rs] xor regFile[rt]) > 0){
                  pc = pc + (simm << 2);
               }
               break;
    case 0x09: D(cout << "addiu " << regNames[rt] << ", " << regNames[rs] << ", " << dec << simm);
               aluOp = ADD;
               aluSrc1 = simm;
               aluSrc2 = regFile[rs];
               writeDest = true;
               destReg = rt;
               break;
    case 0x0c: D(cout << "andi " << regNames[rt] << ", " << regNames[rs] << ", " << dec << uimm);
               aluOp = AND;
               aluSrc1 = regFile[rs];
               aluSrc2 = uimm;
               writeDest = true;
               destReg = rt;
               break;
    case 0x0f: D(cout << "lui " << regNames[rt] << ", " << dec << simm);
               aluOp = SHF_L;
               aluSrc1 = simm;
               aluSrc2 = 16;
               writeDest = true;
               destReg = rt;
               break;
    case 0x1a: D(cout << "trap " << hex << addr);
               switch(addr & 0xf) {
                 case 0x0: cout << endl; break;
                 case 0x1: cout << " " << (signed)regFile[rs];
                           break;
                 case 0x5: cout << endl << "? "; cin >> regFile[rt];
                           break;
                 case 0xa: stop = true; break;
                 default: cerr << "unimplemented trap: pc = 0x" << hex << pc - 4 << endl;
                          stop = true;
               }
               break;
    case 0x23: D(cout << "lw " << regNames[rt] << ", " << dec << simm << "(" << regNames[rs] << ")");
               opIsLoad = true;
               aluOp = ADD;
               aluSrc1 = regFile[rs];
               aluSrc2 = simm;
               writeDest = true;
               destReg = rt;
               break;
    case 0x2b: D(cout << "sw " << regNames[rt] << ", " << dec << simm << "(" << regNames[rs] << ")");
               opIsStore = true;
               aluOp = ADD;
               aluSrc1 = regFile[rs];
               aluSrc2 = simm;
               storeData = regFile[rt];
               break;
    default: cerr << "unimplemented instruction: pc = 0x" << hex << pc - 4 << endl;
  }
  D(cout << endl);
}

void CPU::execute() {
  aluOut = alu.op(aluOp, aluSrc1, aluSrc2);
}

void CPU::mem() {
  if(opIsLoad)
    writeData = dMem.loadWord(aluOut);
  else
    writeData = aluOut;

  if(opIsStore)
    dMem.storeWord(storeData, aluOut);
}

void CPU::writeback() {
  if(writeDest && destReg > 0) // skip if write to reg 0
    regFile[destReg] = writeData;

  if(opIsMultDiv) {
    hi = alu.getUpper();
    lo = alu.getLower();
  }
}

void CPU::printRegFile() {
  cout << hex;
  for(int i = 0; i < NREGS; i++) {
    cout << "    " << regNames[i];
    if(i > 0) cout << "  ";
    cout << ": " << setfill('0') << setw(8) << regFile[i];
    if( i == (NREGS - 1) || (i + 1) % 4 == 0 )
      cout << endl;
  }
  cout << "    hi   : " << setfill('0') << setw(8) << hi;
  cout << "    lo   : " << setfill('0') << setw(8) << lo;
  cout << dec << endl;
}

void CPU::printFinalStats() {
  cout << "Program finished at pc = 0x" << hex << pc << "  ("
       << dec << instructions << " instructions executed)" << endl;
}
