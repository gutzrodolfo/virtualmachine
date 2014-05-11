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
    }
    as.close();
    VirtualMachine machine;
}

void os::decide() {
    decide_wq();       
    decide_run();        
    decide_rq();        
}

void os::decide_run() {
    if (machine.sr.status.r_status == 1) {
        if (jobs.size() == 1) {
            decide_wq();
        }
        erase();
    }
    else if (machine.sr.status.r_status == 6 or machine.sr.status.r_status == 7) {
        waitQ.push(running); 
    }
    else {
        readyQ.push(running);
    }
}

void os::decide_wq() {
    if (waitQ.empty()) {
        return;
    }
    else {
        io();
    }
}

void os::io() {
    PCB * temp = waitQ.front();
    waitQ.pop();
    if (machine.sr.status.r_status == 6) {
        temp -> in >> temp -> read;
        cout << "Reading from process" << temp -> pname << endl;
        cout << "ReadFirst " << temp -> read << endl;
    }
    else if (machine.sr.status.r_status == 7) {
        cout << "Write to process" << temp -> pname << endl;
        cout << "to write" <<temp -> registers[temp -> sr.status.io_reg] << endl;
        temp -> write = temp -> registers[temp -> sr.status.io_reg];
    }
    readyQ.push(temp);
}

void os::decide_rq() {
    if (readyQ.empty()) {
        return;
    }
    else {
        readyQ.pop();
        if (readyQ.empty()) {
            return;
        }
        else {
            running = readyQ.front();
        }
    }
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
        running -> pc = running -> base;
    }
    machine.pc = 0;
    running = readyQ.front();
}


void os::erase() {
    PCB * temp;
    for (list<PCB *>::iterator it = jobs.begin(); it != jobs.end(); it++) {
        temp = *it;
        if(running ->pname == temp -> pname) {
            jobs.erase(it);
        }
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
        if (machine.sr.status.r_status == 6) {
            machine.read_helper(running -> read);
            machine.sr.status.r_status = 0;
        }
        else if (machine.sr.status.r_status == 7) {
            machine.write_helper(running -> write);
            machine.sr.status.r_status = 0;
        }
        machine.parse();
        machine.base = running -> base;
        running -> modify(machine.r, machine.sr, machine.pc + 1, machine.sp, machine.base,  machine.limit);
        decide();
        machine.change(&(running -> in), &(running -> o), &(running -> st), &(running -> out), running -> pc, running -> sr.instr, 
        running -> sp, running-> base, running -> limit, running -> registers);        
    }
}