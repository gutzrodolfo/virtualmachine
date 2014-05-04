/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

PCB.cpp
**********************************************/

#include "PCB.h"
#include <vector>
#include <fstream>

using namespace std;

/****************************************************************************
Declaration of only functions available to PCB one starts the process the 
other is used by the VM and OS to modify or read the containing data that is 
necessary.
*****************************************************************************/

PCB::PCB(string filename) {
	string name = filename + ".in";
	in.open(name.c_str());
	name = filename + ".o";
	o.open(name.c_str());
	name = filename + ".st";
	st.open(name.c_str());
	name = filename + ".out";
	out.open(name.c_str());
}

void PCB::modify(vector<int> registers, ifstream in, ifstream o, fstream st, ofstream out, int pc, int sr, int sp, int base,  int limit) {
	this -> registers = registers;
	this -> pc = pc;
	this -> sr = sr;
	this -> sp = sp;
	this -> base = base;
	this -> limit = limit;
}