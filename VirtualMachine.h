#include <vector>
#include <string>
#include <map>

class VirtualMachine {

private:
  static const int REG_FILE_SIZE = 4;
  static const int MEM_SIZE = 256;
  vector <int> r;
  vector <int> mem;
  int pc, ir, sr, sp, clock, base, limit;
  string irb; //IR in binary form
  typedef void (VirtualMachine::*function)();
  map<string, function> functions;
  ifstream o, in;
  ofstream out;
public:
  VirtualMachine(string filename);
  //These are all available operation by the VM
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
};

  