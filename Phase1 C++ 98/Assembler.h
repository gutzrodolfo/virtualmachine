/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date: 	    04/21/2014
Class:	    CSE 460 

Assembler.h
**********************************************/
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

class Assembler {
 
 public:
    Assembler(string filename);
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
	void halt(); 
	void noop();
	bool error();

private:
	typedef void (Assembler::*function)();
	map<string, function> functions;
 	ifstream in; ofstream out; 
 	string opcode;
 	int rd, rs, constant, addr, machcode; 
};