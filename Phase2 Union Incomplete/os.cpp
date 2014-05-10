/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

os.cpp
**********************************************/

#include "os.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

/******************************************************************
Initialize the data thath the os will use including the PCB's and
the assemblers.
******************************************************************/
os::os() {
    system("ls *.s > progs");
    ifstream as;
    as.open("progs");
    string name;
    while (as >> name) {
        assembled.push_back(new Assembler(name.substr(0, name.size() - 2)));
        jobs.push_back(new PCB(name.substr(0, name.size() - 2)));
        cout << name.substr(0, name.size() - 2) << endl;
    }
    as.close();
    VirtualMachine machine;
}

/*********************************************************************
The os will now assemble all of the instructions. These will be saved 
into the corresponding .o files. 
**********************************************************************/
void os::assemble() {
    for (int i = 0; i < assembled.size(); i++) {
        assembled[i]->parse();
    }
}

/*********************************************************************
Instrcutions shall now be loaded by the the os on to the VM the os 
will also fill the ready queue with all processes and give the PCB the
info that is needed for initialization.
*********************************************************************/
void os::load() {
    for (list<PCB *>::iterator it = jobs.begin(); it != jobs.end(); ++it) {
        running = *it;
        readyQ.push(*it);
        fstream * temp = &running -> o;
        machine.mem_load(temp);
        running -> base = machine.base;
        running -> limit = machine.limit;
        stop++;
    }
    machine.pc = 0;
    running = readyQ.front();
}


void os::erase() {
    PCB * temp;
    for (list<PCB *>::iterator it = jobs.begin(); it != jobs.end(); ++it) {
        temp = *it;
        if(running ->pname == temp -> pname) {
            jobs.erase(it);
        }
        it++;
    }
}


/************************************************************************
This is the heart of the os it will handle the running of all processes
it will use the PCB, the VM, the readyQ, and the waitQ. Additionally, it 
will handle any I/O process. The OS will only terminate once all the
processes are finished.
*************************************************************************/
void os::run() {
    while (!jobs.empty()){
        cout << running-> pname << endl;
        machine.change(&(running -> in), &(running -> o), &(running -> st), &(running -> out), running -> pc, running -> sr, 
        running -> sp, running-> base, running -> limit, running -> registers);
        machine.parse();
        readyQ.pop();
        if (machine.sr.status.r_status == 1) {
            erase();
        }
        cout << machine.pc << endl; 
        running -> modify(machine.r, machine.pc, machine.sr.instr, machine.sp, machine.base, machine.limit);
        if (!readyQ.empty()) {
            running = readyQ.front();
        }
        running -> pc = machine.pc;        
    }
}