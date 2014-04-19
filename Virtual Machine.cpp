#include "VirtualMachine.h"
#include "conversions.h"
#include <map>
#include <fstream>
#include <string>

using namespace std;

VirtualMachine::VirtualMachine(string filename) {
	//Initialize all values 
	r = vector <int> (REG_FILE_SIZE);
    mem = vector <int> (MEM_SIZE);
    pc = 0;  base = 0; sr = 0; sp = 256; ir = 0;  clock = 0; limit = 0;
    //Open files and load memory
    o.open(filename + ".o");
    in.open(filename + ".in");
    out.open(filename + ".out");
    while (!o.eof()) {
    	int x;
    	getline(o, x);
    	mem[i] = x;
    	limit++;
    }
    
    //Now load the map pointers to map the functions using the opcodes
    //Some will not be needed to be added here as the immediate bit needs
    //Be checked first

    typedef void (Assembler::*function)();
	functions["00000"] = &Assembler::load;
	//functions["loadi"] = &Assembler::loadi; Not needed as "I" will call it
	functions["00001"] = &Assembler::store;
	functions["00010"] = &Assembler::add;
	//functions["addi"] = &Assembler::addi;
	functions["00011"] = &Assembler::addc;
	//functions["addci"] = &Assembler::addci;
	functions["00100"] = &Assembler::sub;
	//functions["subi"] = &Assembler::subi;
	functions["00101"] = &Assembler::subc;
	//functions["subci"] = &Assembler::subci;
	functions["00110"] = &Assembler::ander;
	//functions["andi"] = &Assembler::andi;
	functions["00111"] = &Assembler::xorer;
	//functions["xori"] = &Assembler::xori;
	functions["01000"] = &Assembler::negate;
	functions["01001"] = &Assembler::shl;
	functions["01010"] = &Assembler::shla;
	functions["01011"] = &Assembler::shr;
	functions["01100"] = &Assembler::shra;
	functions["01101"] = &Assembler::compr;
	//functions["compri"] = &Assembler::compri;
	functions["01110"] = &Assembler::getstat;
	functions["01111"] = &Assembler::putstat;
	functions["10000"] = &Assembler::jump;
	functions["10001"] = &Assembler::jumpl;
	functions["10010"] = &Assembler::jumpe;
	functions["10011"] = &Assembler::jumpg;
	functions["10100"] = &Assembler::call;
	functions["10101"] = &Assembler::ret;
	functions["10110"] = &Assembler::read;
	functions["10111"] = &Assembler::write;
	functions["11000"] = &Assembler::halt;
	functions["11001"] = &Assembler::noop;
}

  void VirtualMachine::load() {
  	r[btd(irb[5:6])] = mem[btd(irb[8:15])];
  }
  void VirtualMachine::loadi() {
  	r[btd(irb[5:6])] = mem[btd(irb[8:15])];
  }
  void VirtualMachine::store() {
  	mem[btd(irb[8:15])] = r[btd(irb[5:6])];
  }
  void VirtualMachine::add();
  void VirtualMachine::addi();
  void VirtualMachine::addc();
  void VirtualMachine::addci();
  void VirtualMachine::sub();
  void VirtualMachine::subi();
  void VirtualMachine::subc();
  void VirtualMachine::subci();
  void VirtualMachine::ander();
  void VirtualMachine::andi();
  void VirtualMachine::xorer();
  void VirtualMachine::xori();
  void VirtualMachine::negate() {
  	string temp = dtb(r[btd(irb[5:6])], 16);
  	for (int i = 0; i < 16; i++) {
  		if (temp[i] == "1") {
  			temp[i] = "0";
  		}
  		else {
  			temp[i] = "1";
  		}
  		r[btd(irb[5:6])] = btd(temp);
  	}
  }
  void VirtualMachine::shl();
  void VirtualMachine::shla();
  void VirtualMachine::shr();
  void VirtualMachine::shra();
  void VirtualMachine::compr() {
  	string temp = dtb(sr, 16);
  	if (r[btd(irb[5:6])] == r[btd(irb[8:9])]) {
  		sr = btd(temp[0:11] + "010" + temp[15]);
  	}
  	if (r[btd(irb[5:6])] < r[btd(irb[8:9])]) {
  		sr = btd(temp[0:11] + "100" + temp[15]));
  	}
  	if (r[btd(irb[5:6])] > r[btd(irb[8:9])]) {
  		sr = btd(temp[0:11] + "001" + temp[15]);
  	}  	  	
  }
  void VirtualMachine::compri() {
  	  	string temp = dtb(sr, 16);
  	if (r[btd(irb[5:6])] == btd(irb[8:15]) {
  		sr = btd(temp[0:11] + "010" + temp[15]);
  	}
  	if (r[btd(irb[5:6])] < btd(irb[8:15]) {
  		sr = btd(temp[0:11] + "100" + temp[15]));
  	}
  	if (r[btd(irb[5:6])] > btd(irb[8:15]) {
  		sr = btd(temp[0:11] + "001" + temp[15]);
  	}  	  	
  }
  }
  void VirtualMachine::getstat() {
  	r[btd(irb[5:6])] = sr;
  }
  void VirtualMachine::putstat() {
  	sr = r[btd(irb[5:6])];
  }
  void VirtualMachine::jump() {
  	pc = mem[btd(irb[8:15])];
  }
  void VirtualMachine::jumpl() {
  	string temp = dtb(sr, 16);
  	if (temp[12] == "1") {
  		pc = mem[btd(irb[8:15])];
  	}
  }
  void VirtualMachine::jumpe() {
  	string temp = dtb(sr, 16);
  	if (temp[13] == "1") {
  		pc = mem[btd(irb[8:15])];
  	}
  }
  void VirtualMachine::jumpg() {
  	string temp = dtb(sr, 16);
  	if (temp[14] == "1") {
  		pc = mem[btd(irb[8:15])];
  	}  	
  }
  void VirtualMachine::call() {
  	mem[sp] = pc;
  	mem[--sp] = r[0];
  	mem[--sp] = r[1];
  	mem[--sp] = r[2];
  	mem[--sp] = r[3];
  	mem[--sp] = sr;
  	sp--;
  	pc = btd(irb[8:15]);
  }
  void VirtualMachine::ret() {
  	sr = mem[++sp]; 
  	r[3] = mem[++sp];
  	r[2] = mem[++sp];
  	r[1] = mem[++sp];
  	r[0] = mem[++sp];
  	pc = mem[++sp];
   }
  void VirtualMachine::read() {
  	in >> r[btd(irb[5:6])];
  }
  void VirtualMachine::write() {
  	out << r[btd(irb[5:6])]  << endl;
  }
  void VirtualMachine::halt()  {
  	pc = limit;
  } 
  void VirtualMachine::noop() {
  	return;
  } 
