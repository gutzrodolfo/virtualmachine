/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

VirtualMachine.h
**********************************************/
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <limits>
#include "conversions.h"

using namespace std;

class VirtualMachine {

private:
  static const int REG_FILE_SIZE = 4;
  static const int MEM_SIZE = 256;
  vector <int> r;
  vector <int> mem;
  int pc, clk, sp, base, limit; 
  int carry, max_sp;
  long double timestamp, endtimestamp; 
  codes ir, sr;
  typedef void (VirtualMachine::*function)();
  map<int, function> functions;
  fstream *o, *in, *st;
  fstream *out;
  bool retn; 
  friend class os;
public:
  VirtualMachine();
  //These are all available operation by the VM
  void change( fstream *, fstream *, fstream *, fstream *, int, int, int, int, int, int, int, vector<int> ); 
  void parse(); 
  void load();
  void loadi();
  void store();
  void add();
  void addi();
  void addc();
  void addci();
  void sub();
  void subi();
  void subc();
  void subci();
  void ander();
  void andi();
  void xorer();
  void xori();
  void negate();
  void shl();
  void shla();
  void shr();
  void shra();
  void compr();
  void compri();
  void getstat();
  void putstat();
  void jump();
  void jumpl();
  void jumpe();
  void jumpg();
  void call();
  void ret();
  void read();
  void read_helper(int);
  void write_helper(int);
  void write();
  void halt(); 
  void noop();
  void overflow(int, int);
  void print();
//  bool error();
  void mem_load(fstream *);
  void stack_save();
  void stack_load();
};
#endif
