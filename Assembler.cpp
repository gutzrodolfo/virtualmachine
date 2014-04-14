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
		return dtb(x, sz);//If positive just call decimal to binary
	}
	else {
		string y;
		x *= -1;//Negate the number
		y = dtb(x, sz);//Take the number get the binary form 
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

int format1(string opcode, int rd, string i, int rs){
	string RD, RS, code;
	RD = dtb(rd, 2); RS = dtb(rs, 2);
	code = opcode + RD + i + RS + "000000";
	return btd(code);
}

int format2(string opcode, int rd, string i, int addr){
	string RD, RS, ADDR, code;
	RD = dtb(rd, 2);
	if (i == "1"){
		ADDR = dtb2(addr, 8);
	}
	else{
		ADDR = dtb(addr, 8);
	}
	code = opcode + RD + i + RS + ADDR;
	return btd(code);
}



// Implementation of Assembler functions

Assembler::Assembler(string filename){
	in.open(filename + ".s");
	out.open(filename + ".o");
}

void Assembler::parse() {
}

void Assembler::load() {
}

void Assembler::loadi() {
}

void Assembler::store() {
}

void Assembler::add() {
}

void Assembler::addi() {
}

void Assembler::addc() {
}

void Assembler::addci() {
}

void Assembler::sub() {
    
}

void Assembler::subi() {
}

void Assembler::subc() {
}

void Assembler::subci() {
}

void Assembler::ander() {
}

void Assembler::andi() {
}

void Assembler::xorer() {
}

void Assembler::xori() {
}

void Assembler::negate() {
}

void Assembler::shl() {
	rd >> in;
	machcode = format1( "01001", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::shla() {
	rd >> in;
	machcode = format1( "01010", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::shr() {
	rd >> in;
	machcode = format1( "01011", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::shra() {
	rd >> in;
	machcode = format1( "01010", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::compr() {
	rd >> in;
	rs << in;
	machcode = format1( "01101", rd, "0", rs );
	out << machcode << "\n";
}

void Assembler::compri() {
	rd >> in;
	addr << in;
	machcode = format2( "01101", rd, "1", addr );
	out << machcode << "\n";
}

void Assembler::getstat() {
	rd >> in;
	machcode = format1( "01110", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::putstat() {
	rd >> in;
	machcode = format1( "01111", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::jump() {
	addr >> in;
	machcode = format2( "10000", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::jumpl() {
	addr >> in;
	machcode = format2( "10001", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::jumpe() {
	addr >> in;
	machcode = format2( "10010", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::jumpg() {
	addr >> in;
	machcode = format2( "10011", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::call() {
	addr >> in;
	machcode = format1( "10100", 0, "0", addr );
	out << machcode << "\n";
}

void Assembler::ret() {
	machcode = format1( "10101", 0, "0", 0 );
	out << machcode << "\n";
}

void Assembler::read() {
	rd >> in;
	machcode = format1( "10110", rd, "0", 0 );
	out << machcode << "\n";
}

void Assembler::write() {
	rd >> in;
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