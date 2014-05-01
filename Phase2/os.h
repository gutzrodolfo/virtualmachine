#include "Assembler.h"
//#include "VirtualMachine.h"
//#include "PCB.h"
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
	vector<Assembler*> assembled;
	//VirtualMachine machine;
public:
	os(); //First make sure that wil the constructor it will assemble all the files
	void assemble();
	void run();
};