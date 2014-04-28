/**********************************************
Phase 1 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

os.cpp
**********************************************/

#include "Assembler.h"
#include "VirtualMachine.h"
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
	//string name = argv[1];
    Assembler as(argv[1]);
    if (as.parse()) {
    	return 0;
    }

    VirtualMachine vm(argv[1]);
    if (vm.parse()) {
    	return 0;
    }
    return 0;
} // main