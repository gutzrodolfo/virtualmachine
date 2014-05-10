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
#include <limits>

using namespace std;

struct r_type {
  unsigned int unused : 6 ;
  unsigned int rs : 2;
  unsigned int imed : 1;
  unsigned int rd : 2;
  unsigned int opcode : 5;
};

struct a_type {
  unsigned int addr : 8;
  unsigned int imed : 1;
  unsigned int rd : 2;
  unsigned int opcode : 5;
};

struct i_type {
  int constant : 8;
  unsigned int imed : 1;
  unsigned int rd : 2;
  unsigned int opcode : 5;
};
struct s_type {
  unsigned int unused : 6;
  unsigned int io_reg : 2;
  unsigned int r_status : 3;
  unsigned int overflow : 1;
  unsigned int less : 1;
  unsigned int equal : 1;
  unsigned int greater : 1;
  unsigned int carry : 1;
};

union codes {
  int instr;
  r_type reg;
  a_type addr;
  i_type imed;
};

class VirtualMachine {

private:
  static const int REG_FILE_SIZE = 4;
  static const int MEM_SIZE = 256;
  vector <int> r;
  vector <int> mem;
  int pc, clk, sp, base, limit; 
  int carry;
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
  void change( fstream *, fstream *, fstream *, fstream *, int, int, int, int, int, vector<int> ); 
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
  void write();
  void halt(); 
  void noop();
  void overflow(int, int);
//  bool error();
  void mem_load(fstream *);
};
