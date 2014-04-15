#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "Assembler.h"
#include <Algorithm>
#include <sstream>
#include <math.h>

using namespace std;

string dtb(int x, int sz){
	string s = "";
	while(x > 0){
		int bin = x % 2;
		stringstream out;
		out << bin;
		s = out.str();
	}
	reverse(s.begin(), s.end());
	if(s.size() < sz) {
		for(int i = 0; i <= sz; i++) {
			s.insert(0, "0");
		}
	}
	return s;
}

string dtb2(int x, int sz){
	if(x >= 0){
		return dtb(x, sz);          //If positive just call decimal to binary
	}
	else {
		string y;
		x *= -1;                    //Negate the number
		y = dtb(x, sz);             //Take the number get the binary form
                                    //Take the 2's complement now
                                    //Negate the entire thing
		for (int i = 0; i < y.size(); i++) {
			if(y[i] == '1') { 
				y[i] = '0';
			}
			else {
				y[i] = '1';
			}
		}
		//Add 1 to the code
		for(int i = y.size() - 1; i >= 0; i--) {
			if(y[i] == '0') {
				y[i] = '1';
				break;
			}
			else {
				y[i] = '0';
			}
		}
		return y;
	}
}

int btd(string code){
	int decimal = 0;
	for(int i = code.size() - 1; i >= 0; i--) {
		if(code[i] == '1'){
			decimal += pow(2, i);
		}
	}
	return decimal;
}

// Instruction format functions

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
	else {
		ADDR = dtb(addr, 8);
	}
	code = opcode + RD + i + RS + ADDR;
	return btd(code);
}

// Implementation of Assembler functions

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

void Assembler::parse() {
	while (!in.eof()) {
		in >> opcode;
		functions[opcode];
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


void Assembler::load() {
    in >> rd;
    in << addr;
    machcode = format2( "00000", rd, "0", addr );
    out << machcode << "\n";
}

void Assembler::loadi() {
    in >> rd;
    in << addr;
    machcode = format2( "00000", rd, "1", addr );
    out << machcode << "\n";
    
}

void Assembler::store() {
    in >> rd;
    in << addr;
    machcode = format2( "00001", rd, "0", addr );
    out << machcode << "\n";
}

void Assembler::add() {
    in >> rd;
    in << rs
    machcode = format1( "00010", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::addi() {
    in >> rd;
    in << addr;
    machcode = format2( "00010", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::addc() {
    in >> rd;
    in << rs;
    machcode = format1( "00011", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::addci() {
    in >> rd;
    in << addr;
    machcode = format2( "00011", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::sub() {
    in >> rd;
    in << rs;
    machcode = format1( "00100", rd, "0", rs );
    out << machcode << "\n";
    
}

void Assembler::subi() {
    in >> rd;
    in << addr;
    machcode = format2( "00100", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::subc() {
    in >> rd;
    in << rs;
    machcode = format1( "00101", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::subci() {
    in >> rd;
    in << addr;
    machcode = format2( "00101", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::ander() {
    in >> rd;
    in << rs;
    machcode = format1( "00110", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::andi() {
    in >> rd;
    in << addr;
    machcode = format2( "00110", rd, "1", addr );
    out << machcode << "\n";
}

void Assembler::xorer() {
    in >> rd;
    in << rs;
    machcode = format1( "00111", rd, "0", rs );
    out << machcode << "\n";
}

void Assembler::xori() {
    in >> rd;
    in << addr;
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
	in << rs;
	machcode = format1( "01101", rd, "0", rs );
	out << machcode << "\n";
}

void Assembler::compri() {
	in >> rd;
	in << addr;
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
	machcode = format1( "10100", 0, "0", addr );
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

void Assembler::halt() {
	machcode = format1( "11000", 0, "0", 0 ); //As  no-op only requires the opcode 0's are placed in the rest
	out << machcode << "\n";
}

void Assembler::noop() {
	machcode = format1( "11001", 0, "0", 0 ); //As  no-op only requires the opcode 0's are placed in the rest
	out << machcode << "\n";
}