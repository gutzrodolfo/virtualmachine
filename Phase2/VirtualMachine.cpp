/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

VirtualMachine.cpp
**********************************************/
#include "VirtualMachine.h"
#include "conversions.h"
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

VirtualMachine::VirtualMachine() {
/************************************************************
The VM constructor needs to be initialized by startiing the
clock, memory, and all the registers. Additionally, this needs
to have input and output. Finally, it needs some instructions.
*************************************************************/

r = vector <int> (REG_FILE_SIZE);
mem = vector <int> (MEM_SIZE);
pc = 0;  base = 0; sr = 0; sp = 255; ir = 0;  clk = 0; limit = 0;

/********************************************
These are the functions that will called 
through map pointers it should be noted that
not all functions are included here as they 
use the immediate bit and it was more
convenient to call through the corresponding
non-immediate function.
********************************************/
typedef void (VirtualMachine::*function)();
functions["00000"] = &VirtualMachine::load;
functions["00001"] = &VirtualMachine::store;
functions["00010"] = &VirtualMachine::add;
functions["00011"] = &VirtualMachine::addc;
functions["00100"] = &VirtualMachine::sub;
functions["00101"] = &VirtualMachine::subc;
functions["00110"] = &VirtualMachine::ander;
functions["00111"] = &VirtualMachine::xorer;
functions["01000"] = &VirtualMachine::negate;
functions["01001"] = &VirtualMachine::shl;
functions["01010"] = &VirtualMachine::shla;
functions["01011"] = &VirtualMachine::shr;
functions["01100"] = &VirtualMachine::shra;
functions["01101"] = &VirtualMachine::compr;
functions["01110"] = &VirtualMachine::getstat;
functions["01111"] = &VirtualMachine::putstat;
functions["10000"] = &VirtualMachine::jump;
functions["10001"] = &VirtualMachine::jumpl;
functions["10010"] = &VirtualMachine::jumpe;
functions["10011"] = &VirtualMachine::jumpg;
functions["10100"] = &VirtualMachine::call;
functions["10101"] = &VirtualMachine::ret;
functions["10110"] = &VirtualMachine::read;
functions["10111"] = &VirtualMachine::write;
functions["11000"] = &VirtualMachine::halt;
functions["11001"] = &VirtualMachine::noop;

/************************************************************
After the functions have been mapped and values initialized 
the contructor loads all the machine instructions int memory.
*************************************************************/
}

/************************************************************
This can be considered the main function of the program as it
parses through the instructions after they have been loaded on
to the VM. It handle the program counter and call the 
corresponding instruction.
*************************************************************/
bool VirtualMachine::parse() {
  for(pc = 0; pc < limit - 1; pc++) {
    ir = mem[pc];
      //For testing purposes registers will be displayed all times
    irb = dtb(ir, 16);
    (*this.*functions[irb.substr(0,5)])();
    if (error()) {
      return true;
    }
  }
  in -> close();
  out -> close();
  return false; 
}

/************************************************************
These are all the VM is able to do with this the VM will be
able to execute. Through these the different operations are 
able to be preformed. These also call on the conversions.h 
file as it was better to leave those functions and focus on 
writing the code here.
*************************************************************/
void VirtualMachine::load() {
  if (irb[7] == '1') {
    loadi();
    return;
  }
  r[btd(irb.substr(5,2))] = mem[btd(irb.substr(8,8))];
  clk += 4;
}
void VirtualMachine::loadi() {
 r[btd(irb.substr(5,2))] = btd2(irb.substr(8,8));
 clk += 1;
}
void VirtualMachine::store() {
 mem[btd(irb.substr(8,8))] = r[btd(irb.substr(5,2))];
 clk += 4;
}
void VirtualMachine::add() {
  if (irb[7] == '1') {
    addi();
    return;
  }
  char carry = '0';
  overflow(r[btd(irb.substr(5,2))], r[btd(irb.substr(8,2))]);
  r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], r[btd(irb.substr(8,2))], carry);
  string temp = dtb(sr, 16);
  sr = btd(temp.substr(0,15) + carry);    
  clk += 1;
}
void VirtualMachine::addi() {
  char carry = '0';
  overflow(r[btd(irb.substr(5,2))], btd2(irb.substr(8,8)));
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], btd2(irb.substr(8,8)), carry);
    string temp = dtb(sr, 16);
    sr = btd(temp.substr(0,15) + carry); 
    clk += 1;
  }
  void VirtualMachine::addc() {
    if (irb[7] == '1') {
      addci();
      return;
    } 
    char carry = '0';
    overflow(r[btd(irb.substr(5,2))], r[btd(irb.substr(8,2))] );
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], r[btd(irb.substr(8,2))], carry);
    string temp = dtb(sr, 16);
    overflow(r[btd(irb.substr(5,2))], carry);
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], btd(temp.substr(15,1)), carry);
    sr = btd(temp.substr(0,15) + carry); 
    clk += 1;
  }
  void VirtualMachine::addci() {
    char carry = '0';
    overflow(r[btd(irb.substr(5,2))], btd2(irb.substr(8,8)) );
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], btd2(irb.substr(8,8)), carry);
    string temp = dtb(sr, 16);
    overflow(r[btd(irb.substr(5,2))], carry);
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], btd(temp.substr(15,1)), carry);
    sr = btd(temp.substr(0,15) + carry); 
    clk += 1;
  }
  void VirtualMachine::sub() {
    if (irb[7] == '1') {
      subi();
      return;
    }
    char carry = '0';
    overflow(r[btd(irb.substr(5,2))], -r[btd(irb.substr(8,2))]);
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], -r[btd(irb.substr(8,2))], carry);
    string temp = dtb(sr, 16);
    sr = btd(temp.substr(0,15) + carry);    
    clk += 1;
  }
  void VirtualMachine::subi() {
    char carry = '0';
    overflow(r[btd(irb.substr(5,2))], - btd2(irb.substr(8,8)) );
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], -btd2(irb.substr(8,8)), carry);
    string temp = dtb(sr, 16);
    sr = btd(temp.substr(0,15) + carry);     
    clk += 1;
  }
  void VirtualMachine::subc() {
    if (irb[7] == '1') {
      subci();
      return;
    }
    char carry = '0';
    overflow(r[btd(irb.substr(5,2))], -r[btd(irb.substr(8,2))]);
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], -r[btd(irb.substr(8,2))], carry);
    string temp = dtb(sr, 16);
    overflow(r[btd(irb.substr(5,2))], -carry);
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], -btd(temp.substr(15,1)), carry);
    sr = btd(temp.substr(0,15) + carry); 
    clk += 1;
  }
  void VirtualMachine::subci() {
    char carry = '0';
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], -btd2(irb.substr(8,8)), carry);
    string temp = dtb(sr, 16);
    overflow(r[btd(irb.substr(5,2))], -carry);
    r[btd(irb.substr(5,2))] = adder(r[btd(irb.substr(5,2))], -btd(temp.substr(15,1)), carry);
    sr = btd(temp.substr(0,15) + carry); 
    clk += 1;
  }
  void VirtualMachine::ander() {
    if (irb[7] == '1') {
      andi();
      return;
    }
    r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] & r[btd(irb.substr(8,2))];
    clk += 1;
  }
  void VirtualMachine::andi() {
    r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] & btd2(irb.substr(8,8));
    clk += 1;
  }
  void VirtualMachine::xorer() {
    if (irb[7] == '1') {
      xori();
      return;
    }
    r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] ^ r[btd(irb.substr(8,2))];
    clk += 1;
  }
  void VirtualMachine::xori() {
    r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] ^ btd2(irb.substr(8,8));
    clk += 1;
  }
  void VirtualMachine::negate() {
   r[btd(irb.substr(5,2))] = ~r[btd(irb.substr(5,2))];
   clk += 1;
 }
 void VirtualMachine::shl() {
  string temp = dtb(r[btd(irb.substr(5,2))], 16);
  if (temp[0] == '1') {
    sr = btd(temp.substr(0,14) + "1");
  }
  else {
    sr = btd(temp.substr(0,14) + "0");
  }
  r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] << 1;
  clk += 1;
}
void VirtualMachine::shla() {
  string temp = dtb(r[btd(irb.substr(5,2))], 16);
  if (temp[0] == '1') {
    sr = btd(temp.substr(0,14) + "1");
  }
  else {
    sr = btd(temp.substr(0,14) + "0");
  }
  r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] *= 2;
  clk += 1;
}
void VirtualMachine::shr() {
  string temp = dtb(r[btd(irb.substr(5,2))], 16);
  if (temp[15] == '1') {
    sr = btd(temp.substr(0,14) + "1");
  }
  else {
    sr = btd(temp.substr(0,14) + "0");
  }
  r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] >> 1;
  clk += 1;
}
void VirtualMachine::shra() {
  string temp = dtb(r[btd(irb.substr(5,2))], 16);
  if (temp[15] == '1') {
    sr = btd(temp.substr(0,14) + "1");
  }
  else {
    sr = btd(temp.substr(0,14) + "0");
  }  
  r[btd(irb.substr(5,2))] = r[btd(irb.substr(5,2))] /= 2;
  clk += 1;
}
void VirtualMachine::compr() {
  if (irb[7] == '1') {
    compri();
    return;
  }
  string temp = dtb(sr, 16);
  if (r[btd(irb.substr(5,2))] == r[btd(irb.substr(8,2))]) {
    sr = btd(temp.substr(0,12) + "010" + temp.substr(15,1));
  }
  if (r[btd(irb.substr(5,2))] < r[btd(irb.substr(8,2))]) {
    sr = btd(temp.substr(0,12) + "100" + temp.substr(15,1));
  }
  if (r[btd(irb.substr(5,2))] > r[btd(irb.substr(8,2))]) {
    sr = btd(temp.substr(0,12) + "001" + temp.substr(15,1));
  } 
  clk += 1; 	  	
}
void VirtualMachine::compri() {
 string temp = dtb(sr, 16);
 if (r[btd(irb.substr(5,2))] == btd2(irb.substr(8,8))) {
  sr = btd(temp.substr(0,12) + "010" + temp.substr(15,1));
}
if (r[btd(irb.substr(5,2))] < btd2(irb.substr(8,8))) {
  sr = btd(temp.substr(0,12) + "100" + temp.substr(15,1));
}
if (r[btd(irb.substr(5,2))] > btd2(irb.substr(8,8))) {
  sr = btd(temp.substr(0,12) + "001" + temp.substr(15,1));
}  
clk += 1;	  	
}
void VirtualMachine::getstat() {
 r[btd(irb.substr(5,2))] = sr;
 clk += 1;
}
void VirtualMachine::putstat() {
 sr = r[btd(irb.substr(5,2))];
 clk += 1;
}
void VirtualMachine::jump() {
 pc = btd(irb.substr(8,8)) - 1;
 clk += 1;
}
void VirtualMachine::jumpl() {
 string temp = dtb(sr, 16);
 if (temp[12] == '1') {
  pc = btd(irb.substr(8,8)) - 1;
}
clk += 1;
}
void VirtualMachine::jumpe() {
 string temp = dtb(sr, 16);
 if (temp[13] == '1') {
  pc = btd(irb.substr(8,8)) - 1;
}
clk += 1;
}
void VirtualMachine::jumpg() {
 string temp = dtb(sr, 16);
 if (temp[14] == '1') {
  pc = btd(irb.substr(8,8)) - 1;
}  	
clk += 1;
}
void VirtualMachine::call() {
 mem[sp] = pc;
 mem[--sp] = r[0];
 mem[--sp] = r[1];
 mem[--sp] = r[2];
 mem[--sp] = r[3];
 mem[--sp] = sr;
 sp--;
 pc = btd(irb.substr(8,8)) - 1;
 clk += 4;
}
void VirtualMachine::ret() {
 sr = mem[++sp]; 
 r[3] = mem[++sp];
 r[2] = mem[++sp];
 r[1] = mem[++sp];
 r[0] = mem[++sp];
 pc = mem[++sp];
 clk += 4;
}
void VirtualMachine::read() {
 *in >> r[btd(irb.substr(5,2))];
 clk += 28;
}
void VirtualMachine::write() {
 *out << r[btd(irb.substr(5,2))]  << endl;
 clk += 28;
}
void VirtualMachine::halt()  {
 pc = limit;
 *out << "The clock count is: "  << clk << endl;
 clk += 1;
} 
void VirtualMachine::noop() {
  clk += 1;
  return;
}
void VirtualMachine::overflow(int x, int y) {
  string temp = dtb(sr, 16);
  if(x <= 0 and -y <= 0) {
    return;
  }
  else if (x >= 0 and -y >= 0) {
    return;
  }
  else if (x>= 0 and y >= 0) {
    if(x + y == 65535) {
      sr = btd(temp.substr(0,11) + "1" + temp.substr(13,3));
    }
    else {
      return;
    }
  }
  else if (x<= 0 and y <= 0) {
    if(-x + -y == 65536) {
      sr = btd(temp.substr(0,11) + "1" + temp.substr(13,3));
    }
    else {
      return;
    }
  }    
} 
bool VirtualMachine::error() {
  if (!(sp <= 256 or sp >= limit + 6)) {
    cout << "Warning the stack is overflowed! Not enough memory!\n";
    return true;
  }
  return false;
}

//Function added to share between processes
void VirtualMachine::mem_load (fstream *loaded) {
  o = loaded;
  base = pc; 
  limit = 0;  
  vector<int> temp;    
  while (!o -> eof()) {
    int x;
    *o >> x;
    o -> ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    mem[base] = x;
    cout << mem[base] << endl;
    limit++;
    base++;
  }
  o->close();
  pc = base;
  base -= limit;
}


