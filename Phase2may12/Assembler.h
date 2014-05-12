/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date: 	    04/21/2014
Class:	    CSE 460 

Assembler.h
**********************************************/
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <limits>
#include "conversions.h"

using namespace std;

class Assembler {
 
 public:
    Assembler(string filename);
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

private:
	typedef void (Assembler::*function)();
	map<string, function> functions;
 	fstream in; fstream out; 
 	string opcode;
 	int rd, rs, addr, constant;
 	codes code; 
};
#endif