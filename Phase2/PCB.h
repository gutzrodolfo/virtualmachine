#include <vector>
#include <fstream>
#include "VirtualMachine.h"
#include "os.h"
using namesapce std;

/****************************************************************************
This class PCB will be Process control block it will handle the information
of each process. By doing so the VM shall be able to handle time sharing of
each object and thus will be able to run all of them. The VM will need a 
linked list of these objects.
*****************************************************************************/
class PCB
{
private:
	vector<int> registers;
	ifstream *in, *s, *out;
	ofstream *out, 
	int pc, sr, sp, base, limit;
	//Declaring the friend classes
	friend class VirtualMachine;
	friend class os;
public:
	PCB();
	modify();
};