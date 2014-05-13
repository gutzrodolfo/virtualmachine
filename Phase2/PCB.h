/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

PCB.h
**********************************************/

#ifndef PCB_H
#define PCB_H

#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include "unions.h"

using namespace std;

/****************************************************************************
This class PCB will be Process control block it will handle the information
of each process. Rather than closing each file the will point to each file
and the VM will change what files it points to. The in, st, o, out files will
be opened by the PCB and closed at the end.
*****************************************************************************/

class PCB
{
private:
	vector<int> registers;
	fstream in, o, st;
	fstream out;
	int pc, sp, base, limit, read, write;
	codes sr;
	string pname;
	//Declaring the friend classes accounting info later
	int processclk, waitclk, readyclk, before_rq, before_wq;
	int stack;
	friend class VirtualMachine;
	friend class os;
public:
	PCB(string);
	void modify(vector<int>, codes, int, int, long double, int);
	void print(int);
};

#endif