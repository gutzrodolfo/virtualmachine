#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "Assembler.h"

using namespace std;


string dtb(int x){
	return "Test";
}
int btd(string code){

}

// Instruction format functions

int format1(string opcode, int rd, string i, int rs){
	string RD, RS, code;
	RD = dtb(rd); RS = dtb(rs);
	code = opcode + RD + i + RS + "000000";
	return btd(code);
}

int format2(string opcode, int rd, string i, int addr){
	string RD, RS, ADDR, code;
	RD = dtb(rd); RS = dtb(rs);
	if (i == "1"){
		ADDR = dtb2(addr);
	}
	else{
		ADDR = dtb(addr);
	}
	code = opcode + RD + i + RS + ADDR;
	return btd(code);
}
string dtb2(int x){
	return "Test2";
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

void Assember::store() {
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
	out << machcode + "\n";
}

void Assembler::shla() {
	rd >> in;
	machcode = format1( "01010", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::shr() {
	rd >> in;
	machcode = format1( "01011", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::shra() {
	rd >> in;
	machcode = format1( "01010", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::compr() {
	rd >> in;
	rs << in;
	machcode = format1( "01101", rd, "0", rs );
	out << machcode + "\n";
}

void Assembler::compri() {
	rd >> in;
	addr << in;
	machcode = format2( "01101", rd, "1", addr );
	out << machcode + "\n";
}

void Assembler::getstat() {
	rd >> in;
	machcode = format1( "01110", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::putstat() {
	rd >> in;
	machcode = format1( "01111", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::jump() {
	addr >> in;
	machcode = format2( "10000", 0, "0", addr );
	out << machcode + "\n";
}

void Assembler::jumpl() {
	ADDR >> in;
	machcode = format2( "10001", 0, "0", addr );
	out << machcode + "\n";
}

void Assembler::jumpe() {
	addr >> in;
	machcode = format2( "10010", 0, "0", addr );
	out << machcode + "\n";
}

void Assembler::jumpg() {
	addr >> in;
	machcode = format2( "10011", 0, "0", addr );
	out << machcode + "\n";
}

void Assembler::call() {
	addr >> in;
	machcode = format1( "10100", 0, "0", addr );
	out << machcode + "\n";
}

void Assembler::ret() {
	machcode = format1( "10101", 0, "0", 0 );
	out << machcode + "\n";
}

void Assembler::read() {
	rd >> in;
	machcode = format1( "10110", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::write() {
	rd >> in;
	machcode = format1( "10111", rd, "0", 0 );
	out << machcode + "\n";
}

void Assembler::halt() {
	machcode = format1( "11000", 0, "0", 0 ); //As  no-op only requires the opcode 0's are placed in the rest
	out << machcode + "\n";
}

void Assembler::noop() {
	machcode = format1( "11001", 0, "0", 0 ); //As  no-op only requires the opcode 0's are placed in the rest
	out << machcode + "\n";
}