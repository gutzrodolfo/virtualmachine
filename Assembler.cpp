#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "Assembler.h"

using namespace std;
int RD, RS, ADDR, CONST;

string btd(int x){
	return "Test";
}
string btd2(int x){
	return "Test2";
}

Assembler::Assembler(string filename){
	in.open(filename + ".s");
	out.open(filename + ".o");
}

void Assembler::shl(){
	opcode = "01001";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::shla(){
	opcode = "01010";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::shr(){
	opcode = "01011";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::shra(){
	opcode = "01100";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::compr(){
	opcode = "01101";
	RD >> in;
	RS << in;
	rd = btd(RD);
	rs = btd(RS);
	machcode = opcode + rd + "1" + rs + "000000";
	out << machcode + "\n";
}

void Assembler::compri(){
	opcode = "01101";
	RD >> in;
	CONST << in;
	rd = btd(RD);
	constant = btd2(CONST);
	machcode = opcode + rd + "1" + constant;
	out << machcode + "\n";
}

void Assembler::getstat(){
	opcode = "01110";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::putstat(){
	opcode = "01111";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::jump(){
	opcode = "10000";
	ADDR >> in;
	addr = btd(ADDR);
	machcode = opcode + "000" +  addr;
	out << machcode + "\n";
}

void Assembler::jumpl(){
	opcode = "10001";
	ADDR >> in;
	addr = btd(ADDR);
	machcode = opcode + "000" +  addr;
	out << machcode + "\n";
}

void Assembler::jumpe(){
	opcode = "10010";
	ADDR >> in;
	addr = btd(ADDR);
	machcode = opcode + "000" +  addr;
	out << machcode + "\n";
}

void Assembler::jumpg(){
	opcode = "10011";
	ADDR >> in;
	addr = btd(ADDR);
	machcode = opcode + "000" +  addr;
	out << machcode + "\n";
}

void Assembler::call(){
	opcode = "10100";
	ADDR >> in;
	addr = btd(ADDR);
	machcode = opcode + "000" +  addr;
	out << machcode + "\n";
}

void Assembler::ret(){
	machcode = "1010100000000000";
	out << machcode + "\n";
}

void Assembler::read(){
	opcode = "10110";
	RD >> in;
	rd = btd(RD);
	machcode = opcode + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::write(){
	opcode = "10111";
	RD >> in;
	rd = btd(RD);
	machcode = opcode  + rd + "000000000";
	out << machcode + "\n";
}

void Assembler::halt(){
	machcode = "1100000000000000"; //As  no-op only requires the opcode 0's are placed in the rest
	out << machcode + "\n";
}

void Assembler::noop(){
	machcode = "1100100000000000"; //As  no-op only requires the opcode 0's are placed in the rest
	out << machcode + "\n";
}
