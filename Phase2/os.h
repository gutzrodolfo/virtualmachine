/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

os.h
**********************************************/

#ifndef os_H
#define os_H

#include "Assembler.h"
#include "VirtualMachine.h"
#include "PCB.h"
#include <list>
#include <queue>
#include <vector>

using namespace std;

/****************************************************************************
The header file for the os it will handle the virtual machine and the asembler
and run all processes. More functionality will be added as it is confirmed to 
run.
*****************************************************************************/

class os
{
private:
	vector<Assembler *> assembled;
	VirtualMachine machine;
	list <PCB *> jobs;
	queue <PCB *> readyQ, waitQ;
	PCB * running;
	int psize, contextclk, idleclk;
	void erase();
	void decide();
	void decide_run();	
	void decide_rq();
	void decide_wq();
	void io();
	void print();
public:
	os(); //First make sure that wil the constructor it will assemble all the files
	void assemble();
	void load(); //Used to load the files into memory
	void run();
};

#endif