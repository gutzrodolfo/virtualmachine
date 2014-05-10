#include <iostream> 

using namespace std;
struct types
{
	unsigned int unused : 6;
	unsigned int rs : 2;
	unsigned int imed : 1;
	unsigned int rd : 2;
	unsigned int opcode : 5;
};

union codes {
	int instr;
	types c;
};

int main() {
	codes test;
	test.instr = 4288;
	cout << test.c.opcode << "is the opcode" <<  endl;
	cout << test.c.rd << "is the rd" <<  endl;
	cout << test.c.rs << "is the rs" <<  endl;
}