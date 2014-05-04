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

using namespace std;

os::os() {
    system("ls *.s > progs");
    ifstream as;
    as.open("progs");
    string name;
    while (!as.eof()) {
        ifstream in, s, st, o;
        ofstream out;
        getline(as, name);
        assembled.push_back(new Assembler(name.substr(0, name.size() - 2)));
        jobs.push_back(new PCB(name.substr(0, name.size() - 2)));
        //cout << name.substr(0, name.size() - 2) << endl;
    }
    as.close();
    VirtualMachine machine;
}

void os::assemble() {
    for (int i = 0; i < assembled.size() - 1; i++) {
        assembled[i]->parse();
    }
}

void os::load() {
    for (list<PCB *>::iterator it = jobs.begin(); it != jobs.end(); it++){
        //list<PCB *>::iterator it = jobs.begin();
        running = *it;
        machine.mem_load(running -> o);
    }
}