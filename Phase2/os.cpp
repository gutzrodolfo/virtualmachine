/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

os.cpp
**********************************************/

#include "os.h"
//#include "Assembler.h"
//#include "VirtualMachine.h"
//#include "PCB.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

os::os() {
    system("ls *.s > progs");
    ifstream as;
    as.open("progs");
    string name;
    while (!as.eof()) {
        getline(as, name);
        assembled.push_back(new Assembler(name.substr(0, name.size() - 2)));
    }
    as.close();
}

void os::assemble() {
    for (int i = 0; i < assembled.size() - 1; i++) {
        assembled[i]->parse();
    }
}