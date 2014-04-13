#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

class Assembler {
 public:
	Assembler(string filename);//Argument will be passed from the os.cpp file
	void parse();// Will go through the a file to output the .o file
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
 private:
 	typedef void (*pfunc)(string);
 	map<string, pfunc> functions; // Will be mapped to the functions to call them
 	fstream in, out; //One will be the .s file while the other will be the .o file 
 	string opcode, rd, rs, constant, addr, machcode; //Different parts of the opcode
};
