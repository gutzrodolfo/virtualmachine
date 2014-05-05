/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

VirtualMachine.h
**********************************************/
#include <vector>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class VirtualMachine {

private:
  static const int REG_FILE_SIZE = 4;
  static const int MEM_SIZE = 256;
  vector <int> r;
  vector <int> mem;
  int pc, ir, sr, sp, clk, base, limit;
  string irb; //IR in binary form
  typedef void (VirtualMachine::*function)();
  map<string, function> functions;
  fstream *o, *in, *st;
  fstream *out;
  friend class os;
public:
  VirtualMachine();
  //These are all available operation by the VM
  bool parse(); 
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
  void write();
  bool halt(); 
  void noop();
  void overflow(int, int);
  bool error();
  void mem_load(fstream *);
  void print();
};
