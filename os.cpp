#include "Assembler.h"
#include "VirtualMachine.h"
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
	//string name = argv[1];
    Assembler as(argv[1]);
    as.parse();
    VirtualMachine vm(argv[1]);
    vm.parse();
    return 0;
} // main