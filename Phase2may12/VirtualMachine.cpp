/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460
 
VirtualMachine.cpp
**********************************************/
#include "VirtualMachine.h"
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <cassert>
 
using namespace std;
 
VirtualMachine::VirtualMachine() {
/************************************************************
The VM constructor needs to be initialized by startiing the
clock, memory, and all the registers. Additionally, this needs
to have input and output. Finally, it needs some instructions.
*************************************************************/
 
r = vector <int> (REG_FILE_SIZE);
mem = vector <int> (MEM_SIZE);
pc = 0;  base = 0; sr.instr = 0; sp = 255; ir.instr = 0;  clk = 0; limit = 0; max_sp = 0; sr.instr = 0;
retn = false;
timestamp = static_cast<long double> ( time(NULL));
 
/********************************************
These are the functions that will called
through map pointers it should be noted that
not all functions are included here as they
use the immediate bit and it was more
convenient to call through the corresponding
non-immediate function.
********************************************/
typedef void (VirtualMachine::*function)();
functions[0] = &VirtualMachine::load;
functions[1] = &VirtualMachine::store;
functions[2] = &VirtualMachine::add;
functions[3] = &VirtualMachine::addc;
functions[4] = &VirtualMachine::sub;
functions[5] = &VirtualMachine::subc;
functions[6] = &VirtualMachine::ander;
functions[7] = &VirtualMachine::xorer;
functions[8] = &VirtualMachine::negate;
functions[9] = &VirtualMachine::shl;
functions[10] = &VirtualMachine::shla;
functions[11] = &VirtualMachine::shr;
functions[12] = &VirtualMachine::shra;
functions[13] = &VirtualMachine::compr;
functions[14] = &VirtualMachine::getstat;
functions[15] = &VirtualMachine::putstat;
functions[16] = &VirtualMachine::jump;
functions[17] = &VirtualMachine::jumpl;
functions[18] = &VirtualMachine::jumpe;
functions[19] = &VirtualMachine::jumpg;
functions[20] = &VirtualMachine::call;
functions[21] = &VirtualMachine::ret;
functions[22] = &VirtualMachine::read;
functions[23] = &VirtualMachine::write;
functions[24] = &VirtualMachine::halt;
functions[25] = &VirtualMachine::noop;
 
}
 
/************************************************************
This can be considered the main function of the program as it
parses through the instructions after they have been loaded on
to the VM. It handle the program counter and call the
corresponding instruction.
*************************************************************/
void VirtualMachine::parse() {
  for(; pc < base + limit; ) {
    ir.instr = mem[pc];
    cout << "The instruction is" << ir.reg.opcode << endl;
    assert(sr.status.r_status != 6 and sr.status.r_status != 7);
    if (sr.status.r_status == 6 or sr.status.r_status == 7) {
      cout << "Currently reading or writing\n";
      retn = true;
    }
    else {
      cout << "Currently executing" << endl;
      (*this.*functions[ir.reg.opcode])();
      pc++;
    }
    if (retn) {
      cout << "Returning" << endl;
      stack_save();
      retn = false;
      return;
    }
  }
}
void VirtualMachine::change(fstream * a, fstream * b, fstream * c, fstream * d, int t, int v, int w, int x, int y, int clk, int max_sp, vector<int> vec) {
  this -> in = a;
  this -> o = b;
  this -> st = c;
  this -> out = d;
 
  this -> pc = t;
  this -> sr.instr = v; 
  this -> sp = w;
  this -> base = x;
  this -> limit = y;
  this -> clk = clk;
  this -> max_sp = max_sp;
 
  this -> r = vec;
}

void VirtualMachine::print() {
  cout << "The PC is " << pc << endl << "the opcode is: " << ir.reg.opcode << endl;
  cout << "The stack pointer is " << sp << endl;  
  cout << "R[0] = " << r[0] << " R[1] = " << r[1] << " R[2] = " << r[2] << " R[3] = " << r[3] << endl;
  cout << "If mem is needed here it is " << mem[ir.addr.addr] << endl;

}
/************************************************************
These are all the VM is able to do with this the VM will be
able to execute. Through these the different operations are
able to be preformed. These also call on the conversions.h
file as it was better to leave those functions and focus on
writing the code here.
*************************************************************/
void VirtualMachine::load() {
  if (ir.imed.imed == 1) {
    loadi();
    return;
  }
  r[ir.addr.rd] = mem[ir.addr.addr];
  clk += 4;
  print();
}
void VirtualMachine::loadi() {
  r[ir.imed.rd] = ir.imed.constant;
  clk += 1;
  print();
}
void VirtualMachine::store() {
  mem[ir.addr.addr] = r[ir.addr.rd];
  clk += 4;
  print();
}
void VirtualMachine::add() {
  if (ir.imed.imed == 1) {
    addi();
    return;
  }
  sr.status.carry = 0;
  int test = r[ir.reg.rd] + r[ir.reg.rs];
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.reg.rd] + r[ir.reg.rs];
  clk += 1;
  print();
}
void VirtualMachine::addi() {
  sr.status.carry = 0;
  int test = r[ir.imed.rd] + ir.imed.constant;
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.imed.rd] + ir.imed.constant;
  clk += 1;
  print();
}
void VirtualMachine::addc() {
  if (ir.imed.imed == 1) {
    addci();
    return;
  }
  sr.status.carry = 0;
  int test = r[ir.reg.rd] + r[ir.reg.rs] + carry;
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.reg.rd] + r[ir.reg.rs] + carry;
  clk += 1;
  print();
}
void VirtualMachine::addci() {
  sr.status.carry = 0;
  int test = r[ir.imed.rd] + ir.imed.constant + carry;
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.imed.rd] + ir.imed.constant + carry;
  clk += 1;
  print();
}
void VirtualMachine::sub() {
  if (ir.imed.imed == 1) {
    subi();
    return;
  }
  sr.status.carry = 0;
  int test = r[ir.reg.rd] - r[ir.reg.rs];
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.reg.rd] - r[ir.reg.rs];
  clk += 1;
  print();
}
void VirtualMachine::subi() {
  sr.status.carry = 0;
  int test = r[ir.imed.rd] - ir.imed.constant;
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.imed.rd] - ir.imed.constant;
  clk += 1;
  print();
}
void VirtualMachine::subc() {
  if (ir.imed.imed == 1) {
    subci();
    return;
  }
  sr.status.carry = 0;
  int test = r[ir.reg.rd] - r[ir.reg.rs] - carry;
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.reg.rd] - r[ir.reg.rs] - carry;
  clk += 1;
  print();
}
void VirtualMachine::subci() {
  sr.status.carry = 0;
  int test = r[ir.imed.rd] - ir.imed.constant - carry;
  if (test > 32767 or test < -32768) {
    sr.status.carry = 1;
  } 
  r[ir.reg.rd] = r[ir.imed.rd] - ir.imed.constant - carry;
  clk += 1;
  print();
}
void VirtualMachine::ander() {
  if (ir.imed.imed == 1) {
    andi();
    return;
  }
  r[ir.reg.rd] = r[ir.reg.rd] & r[ir.reg.rs];
  clk += 1;
  print();
}
void VirtualMachine::andi() {
  r[ir.reg.rd] = r[ir.reg.rd] & ir.imed.constant;
  clk += 1;
  print();
}
void VirtualMachine::xorer() {
  if (ir.imed.imed == 1) {
    xori();
    return;
  }
  r[ir.reg.rd] = r[ir.reg.rd] ^ r[ir.reg.rs];
  clk += 1;
  print();
}
void VirtualMachine::xori() {
  r[ir.reg.rd] = r[ir.imed.rd] ^ ir.imed.constant;
  clk += 1;
  print();
}
void VirtualMachine::negate() {
  r[ir.reg.rd] = ~r[ir.reg.rd];
  clk += 1;
  print();
}
void VirtualMachine::shl() {
  sr.status.carry = 0;
  r[ir.reg.rd] = r[ir.reg.rd] << 1;
  if (r[ir.reg.rd] > 32767 ) {
    sr.status.carry = 1;
  }
  clk += 1;
  print();
}
void VirtualMachine::shla() {
  sr.status.carry = 0;
  r[ir.reg.rd] = r[ir.reg.rd] *= 2;
  if (r[ir.reg.rd] > 32767 ) {
    sr.status.carry = 1;
  }   
  clk += 1;
  print();
}
void VirtualMachine::shr() {
  sr.status.carry = 0;
  if (r[ir.reg.rd] % 2 == 1 or r[ir.reg.rd] == 1) {
    sr.status.carry = 1;
  }
  r[ir.reg.rd] = r[ir.reg.rd] >> 1;
  clk += 1;
  print();
}
void VirtualMachine::shra() {
  sr.status.carry = 0;
  r[ir.reg.rd] = r[ir.reg.rd] /= 2;
  if (r[ir.reg.rd] % 2 == 1 or r[ir.reg.rd] == 1) {
    sr.status.carry = 1;
  } 
  clk += 1;
  print();
}
void VirtualMachine::compr() {
  if (ir.imed.imed == 1) {
    compri();
    return;
  }
  sr.status.equal = 0;
  sr.status.less = 0;
  sr.status.greater = 0;
  if (r[ir.reg.rd] == r[ir.reg.rs]) {
    sr.status.equal = 1;
  }
  if (r[ir.reg.rd] < r[ir.reg.rs]) {
    sr.status.less = 1;
  }
  if (r[ir.reg.rd] > r[ir.reg.rs]) {
    sr.status.greater = 1;
  }
  clk += 1;  
  print();      
}
void VirtualMachine::compri() {
  sr.status.equal = 0;
  sr.status.less = 0;
  sr.status.greater = 0;
  if (r[ir.imed.rd] == ir.imed.constant) {
    sr.status.equal = 1;
  }
  if (r[ir.imed.rd] < ir.imed.constant) {
    sr.status.less = 1;
  }
  if (r[ir.imed.rd] > ir.imed.constant) {
    sr.status.greater = 1;
  } 
  clk += 1;  
  print();  
}
void VirtualMachine::getstat() {
  r[ir.reg.rd] = sr.instr;
  clk += 1;
  print();
}
void VirtualMachine::putstat() {
  sr.instr = r[ir.reg.rd];
  clk += 1;
  print();
}
void VirtualMachine::jump() {
  pc = ir.addr.addr - 1 + base;
  clk += 1;
  print();
}
void VirtualMachine::jumpl() {
  if (sr.status.less == 1) {
    pc = ir.addr.addr - 1 + base;
  }
  clk += 1;
  print();
}
void VirtualMachine::jumpe() {
  if (sr.status.equal == 1) {
    pc = ir.addr.addr - 1 + base;
  }
  clk += 1;
  print();
}
void VirtualMachine::jumpg() {
  if (sr.status.greater == 1) {
    pc = ir.addr.addr - 1 + base;
  }    
  clk += 1;
  print();
}
void VirtualMachine::call() {
  mem[sp--] = pc;
  mem[sp--] = r[0];
  mem[sp--] = r[1];
  mem[sp--] = r[2];
  mem[sp--] = r[3];
  mem[sp--] = sr.instr;
  pc = base + ir.addr.addr - 1;
  clk += 4;
  if ((255 - sp) > max_sp) {
    max_sp = 255 - sp;
  }
  print();
}
void VirtualMachine::ret() {
  sr.instr = mem[++sp];
  r[3] = mem[++sp];
  r[2] = mem[++sp];
  r[1] = mem[++sp];
  r[0] = mem[++sp];
  pc = mem[++sp];
  clk += 4;
  print();
}
void VirtualMachine::read() {
  sr.status.r_status = 6;
  sr.status.io_reg = ir.reg.rd;
  clk += 1;
  retn = true;
  print();
}
 
void VirtualMachine::read_helper(int read) {
  r[sr.status.io_reg] = read;
}
 
void VirtualMachine::write() {
  sr.status.r_status = 7;
  sr.status.io_reg = ir.reg.rd;
  clk += 1;
  retn = true;
  print();
}
 
void VirtualMachine::write_helper(int write) {
  *out << write << endl;
}
 
void VirtualMachine::halt()  {
  pc = base + limit;
  sr.status.r_status = 1;
  endtimestamp = static_cast<long double> ( time(NULL) );
  cout << "Halting\n";
  *out << "The clock count is: "  << clk << endl;
  clk += 1;
  print();
}
 
void VirtualMachine::noop() {
  clk += 1;
  print();
  return;
}
 
//Function added to share between processes
void VirtualMachine::mem_load (fstream *loaded) {
  o = loaded;
  base = pc;
  limit = 0; 
  vector<int> temp;  
  int to_load;
  while (*o >> to_load) {
    o -> ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    mem[base] = to_load;
    limit++;
    base++;
  }
  pc = base;
  base -= limit;
}
 
void VirtualMachine::stack_save() {
  assert(sp == 255);
  if (sp == 255) {
    return;
  }
  for(int i = this -> sp; i < 256; i++) {
    *st << mem[i];
  }
}
 
void VirtualMachine::stack_load() {
  for (int stack = 255; stack >= sp; stack--) {
    *st >> mem[stack];
  }
}

