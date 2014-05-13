/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

main.cpp
**********************************************/

/*****************************************************************************
Not much to say here the main.cpp file just call the os functions so that they 
will execute. These are first assembling the code. Then loading it on to the 
VM. And finally having the VM execute the code.
******************************************************************************/

#include "os.h"

using namespace std;

int main() {
	os myos;
	myos.assemble();
	myos.load();
	myos.run(); 
	}