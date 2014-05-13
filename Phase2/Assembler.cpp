/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date: 	    04/21/2014
Class:	    CSE 460 

Assembler.cpp
**********************************************/
#include "Assembler.h"
#include <algorithm>

using namespace std;


/*******************************************************
 Loads map pointers to map functions using corresponding
 string opcodes. 
*******************************************************/

Assembler::Assembler(string filename) {
	string name = filename + ".s";
	in.open(name.c_str(), fstream::in);
	name = filename + ".o";
	out.open(name.c_str(), fstream::out);
	typedef void (Assembler::*function)();
	functions["load"] = &Assembler::load;
	functions["loadi"] = &Assembler::loadi;
	functions["store"] = &Assembler::store;
	functions["add"] = &Assembler::add;
	functions["addi"] = &Assembler::addi;
	functions["addc"] = &Assembler::addc;
	functions["addci"] = &Assembler::addci;
	functions["sub"] = &Assembler::sub;
	functions["subi"] = &Assembler::subi;
	functions["subc"] = &Assembler::subc;
	functions["subci"] = &Assembler::subci;
	functions["and"] = &Assembler::ander;
	functions["andi"] = &Assembler::andi;
	functions["xor"] = &Assembler::xorer;
	functions["xori"] = &Assembler::xori;
	functions["compl"] = &Assembler::negate;
	functions["shl"] = &Assembler::shl;
	functions["shla"] = &Assembler::shla;
	functions["shr"] = &Assembler::shr;
	functions["shra"] = &Assembler::shra;
	functions["compr"] = &Assembler::compr;
	functions["compri"] = &Assembler::compri;
	functions["getstat"] = &Assembler::getstat;
	functions["putstat"] = &Assembler::putstat;
	functions["jump"] = &Assembler::jump;
	functions["jumpl"] = &Assembler::jumpl;
	functions["jumpe"] = &Assembler::jumpe;
	functions["jumpg"] = &Assembler::jumpg;
	functions["call"] = &Assembler::call;
	functions["return"] = &Assembler::ret;
	functions["read"] = &Assembler::read;
	functions["write"] = &Assembler::write;
	functions["halt"] = &Assembler::halt;
	functions["noop"] = &Assembler::noop;
}

/*********************************************************
 Reads assembly file and initializes the appropriate assembly
 function.  
********************************************************/

void Assembler::parse() {
	while (in >> opcode) {
		
		if(opcode == "!") {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		code.instr = 0;
    	(*this.*functions[opcode])();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	out.close();
	in.close();
}

/***********************************************
 Implementation of Assembler functions
************************************************/

void Assembler::load() {
	code.addr.opcode = 0;
    in >> rd; 
    code.addr.rd = rd;
    in >>  addr; 
    code.addr.addr = addr;
    out << code.instr << "\n";
}

void Assembler::loadi() {
	code.imed.opcode = 0;
	code.imed.imed = 1;
    in >> rd; 
    code.imed.rd = rd;
    in >> constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
    
}

void Assembler::store() {
	code.addr.opcode = 1;
    in >> rd; 
    code.addr.rd = rd;
    in >> addr;
    code.addr.addr = addr;
    out << code.instr << "\n";
}

void Assembler::add() {
	code.reg.opcode = 2;
    in >> rd;
    code.reg.rd = rd;
    in >>  rs;
    code.reg.rs = rs;
    out << code.instr << "\n";
}

void Assembler::addi() {
	code.imed.opcode = 2;
	code.imed.imed = 1;
    in >> rd;
    code.imed.rd = rd;
    in >>  constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
}

void Assembler::addc() {
	code.reg.opcode = 3;
    in >> rd;
    code.reg.rd = rd;
    in >> rs;
    code.reg.rs = rs;
    out << code.instr << "\n";
}

void Assembler::addci() {
	code.imed.opcode = 3;
	code.imed.imed = 1;
    in >> rd;
    code.imed.rd = rd;
    in >> constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
}

void Assembler::sub() {
	code.reg.opcode = 4;
    in >> rd; 
    code.reg.rd = rd;
    in >> rs; 
    code.reg.rs = rs;
    out << code.instr << "\n";   
}

void Assembler::subi() {
	code.imed.opcode = 4;
	code.imed.imed = 1;
    in >> rd; 
    code.imed.rd = rd;
    in >> constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
}

void Assembler::subc() {
	code.reg.opcode = 5;
    in >> rd; 
    code.reg.rd = rd;
    in >> rs; 
    code.reg.rs = rs;
    out << code.instr << "\n";
}

void Assembler::subci() {
	code.imed.opcode = 5;
	code.imed.imed = 1;
    in >> rd; 
    code.imed.rd = rd;
    in >> constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
}

void Assembler::ander() {
	code.reg.opcode = 6;
    in >> rd; 
    code.reg.rd = rd;
    in >> rs; 
    code.reg.rs = rs;
    out << code.instr << "\n";
}

void Assembler::andi() {
	code.imed.opcode = 6;
	code.imed.imed = 1;
    in >> rd; 
    code.imed.rd = rd;
    in >> constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
}

void Assembler::xorer() {
	code.reg.opcode = 7;
    in >> rd; 
    code.reg.rd = rd;
    in >> rs; 
    code.reg.rs = rs;
    out << code.instr << "\n";
}

void Assembler::xori() {
	code.imed.opcode = 7;
	code.imed.imed = 1;
    in >> rd; 
    code.imed.rd = rd;
    in >> constant;
    code.imed.constant = constant;
    out << code.instr << "\n";
}

void Assembler::negate() {
	code.reg.opcode = 8;
    in >> rd; 
    code.reg.rd = rd;
    out << code.instr << "\n";
}

void Assembler::shl() {
	code.reg.opcode = 9;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::shla() {
	code.reg.opcode = 10;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::shr() {
	code.reg.opcode = 11;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::shra() {
	code.reg.opcode = 12;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::compr() {
	code.reg.opcode = 13;
	in >> rd; 
    code.reg.rd = rd;
	in >> rs; 
    code.reg.rs = rs;
	out << code.instr << "\n";
}

void Assembler::compri() {
	code.imed.opcode = 13;
	code.imed.imed = 1;
	in >> rd; 
    code.imed.rd = rd;
	in >> constant;
    code.imed.constant = constant;
	out << code.instr << "\n";
}

void Assembler::getstat() {
	code.reg.opcode = 14;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::putstat() {
	code.reg.opcode = 15;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::jump() {
	code.addr.opcode = 16;
	in >> addr;
    code.addr.addr = addr;
	out << code.instr << "\n";
}

void Assembler::jumpl() {
	code.addr.opcode = 17;
	in >> addr;
    code.addr.addr = addr;
	out << code.instr << "\n";
}

void Assembler::jumpe() {
	code.addr.opcode = 18;
	in >> addr;
    code.addr.addr = addr;
	out << code.instr << "\n";
}

void Assembler::jumpg() {
	code.addr.opcode = 19;
	in >> addr;
    code.addr.addr = addr;
	out << code.instr << "\n";
}

void Assembler::call() {
	code.addr.opcode = 20;
	in >> addr;
    code.addr.addr = addr;
	out << code.instr << "\n";
}

void Assembler::ret() {
	code.reg.opcode = 21;
	out << code.instr << "\n";
}

void Assembler::read() {
	code.reg.opcode = 22;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

void Assembler::write() {
	code.reg.opcode = 23;
	in >> rd; 
    code.reg.rd = rd;
	out << code.instr << "\n";
}

/**************************************************************
 As  halt & no-op only require 
 the opcodes, 0's are placed in the rest. 
***************************************************************/

void Assembler::halt() {
	code.reg.opcode = 24;
	out << code.instr << "\n";
}

void Assembler::noop() {
	code.reg.opcode = 25;
	out << code.instr << "\n";
}
