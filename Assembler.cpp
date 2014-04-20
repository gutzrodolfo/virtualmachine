/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date: 	 04/21/2014
Class:	 CSE 460 

Assembler.cpp
**********************************************/

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "Assembler.h"
#include <Algorithm>
#include <sstream>
#include "conversions.h"

using namespace std;

/***************************************************
 format1 & format2 functions simplify the translation 
 of their respective instruction formats. For use in 
 the assembly functions. 
***************************************************/

int format1( string opcode, int rd, string i, int rs ) {
	
    string RD, RS, code;
	RD = dtb( rd, 2 ); RS = dtb( rs, 2 );
	code = opcode + RD + i + RS + "000000";
	return btd( code );
}

int format2( string opcode, int rd, string i, int addr ) {
	
    string RD, RS, ADDR, code;
	RD = dtb(rd, 2);
    if ( i == "1" ) {
		ADDR = dtb2(addr, 8);
	}
	else if (i == "0") {
		ADDR = dtb(addr, 8);
	}
	code = opcode + RD + i + RS + ADDR;
	return btd(code);
}

/*******************************************************
 Loads map pointers to map functions using corresponding
 string opcodes. 
*******************************************************/

Assembler::Assembler(string filename) {
	in.open(filename + ".s");
	out.open(filename + ".o");
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
	while (!in.eof()) {
		in >> opcode;
		if(opcode == "!") {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
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
    in >> rd;
    in >>  addr;
    machcode = format2( "00000", rd, "0", addr );
    out << machcode << "\n";
}

void Assembler::loadi() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00000", rd, "1", addr );
    out << machcode << "\n";
    
}

void Assembler::store() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00001", rd, "0", addr );
    out << machcode << "\n";
}

void Assembler::add() {
    in >> rd;
    in >>  rs;
    machcode = format1( "00010", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::addi() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00010", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::addc() {
    in >> rd;
    in >>  rs;
    machcode = format1( "00011", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::addci() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00011", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::sub() {
    in >> rd;
    in >>  rs;
    machcode = format1( "00100", rd, "0", rs );
    out << machcode << "\n";
    
}

void Assembler::subi() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00100", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::subc() {
    in >> rd;
    in >>  rs;
    machcode = format1( "00101", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::subci() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00101", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::ander() {
    in >> rd;
    in >>  rs;
    machcode = format1( "00110", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::andi() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00110", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::xorer() {
    in >> rd;
    in >>  rs;
    machcode = format1( "00111", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::xori() {
    in >> rd;
    in >>  addr;
    machcode = format2( "00111", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::negate() {
    in >> rd;
    machcode = format1( "0000", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::shl() {
	in >> rd;
	machcode = format1( "01001", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::shla() {
	in >> rd;
	machcode = format1( "01010", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::shr() {
	in >> rd;
	machcode = format1( "01011", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::shra() {
	in >> rd;
	machcode = format1( "01010", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::compr() {
	in >> rd;
	in >>  rs;
	machcode = format1( "01101", rd, "0", rs );
	out << machcode << "\n";
}

void Assembler::compri() {
	in >> rd;
	in >>  addr;
	machcode = format2( "01101", rd, "1", addr );
	out << machcode << "\n";
}

void Assembler::getstat() {
	in >> rd;
	machcode = format1( "01110", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::putstat() {
	in >> rd;
	machcode = format1( "01111", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::jump() {
	in >> addr;
	machcode = format2( "10000", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::jumpl() {
	in >> addr;
	machcode = format2( "10001", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::jumpe() {
	in >> addr;
	machcode = format2( "10010", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::jumpg() {
	in >> addr;
	machcode = format2( "10011", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::call() {
	in >> addr;
	machcode = format2( "10100", 0, "0", addr);
	out << machcode << "\n";
}

void Assembler::ret() {
	machcode = format1( "10101", 0, "0", 0 );
	out << machcode << "\n";
}

void Assembler::read() {
	in >> rd;
	machcode = format1( "10110", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::write() {
	in >> rd;
	machcode = format1( "10111", rd, "0", 0 );
	out << machcode << "\n";
}

/**************************************************************
 As  halt & no-op only require 
 the opcodes, 0's are placed in the rest. 
***************************************************************/

void Assembler::halt() {
	machcode = format1( "11000", 0, "0", 0 ); 
	out << machcode << "\n";
}

void Assembler::noop() {
	machcode = format1( "11001", 0, "0", 0 ); 
}