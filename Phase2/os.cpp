/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

os.cpp
**********************************************/

#include "os.h"

using namespace std;

/******************************************************************
Initialize the data thath the os will use including the PCB's and
the assemblers.
******************************************************************/
os::os() {
    system("ls *.s > progs");
    ifstream as;
    as.open("progs");
    string name;
    while (as >> name) {
        assembled.push_back(new Assembler(name.substr(0, name.size() - 2)));
        jobs.push_back(new PCB(name.substr(0, name.size() - 2)));
    }
    psize = jobs.size();
    as.close();
    VirtualMachine machine;
    contextclk = 0; idleclk = 0;
}

/*******************************************************************
The decide functions these handle two things the switching between 
tasks and placing the them in the WaitQ for file I/O.
********************************************************************/
void os::decide() {
    contextclk += 5;
    decide_run();
    decide_wq();              
    decide_rq();        
}

void os::decide_run() {
    if (machine.sr.status.r_status == 1) {
        running -> print(machine.vm_clk);
        idleclk += running -> readyclk + running -> waitclk;
        erase();
    }
    else if (machine.sr.status.r_status == 2 or machine.sr.status.r_status == 3 or machine.sr.status.r_status == 4 
        or machine.sr.status.r_status == 5) {
        cout << "Error" << endl;
        erase();//Error has occured
    }
    else if (machine.sr.status.r_status == 6 or machine.sr.status.r_status == 7) {
        running -> before_wq = machine.vm_clk;
        waitQ.push(running); 
    }
    else {
        running -> before_rq = machine.vm_clk;
        readyQ.push(running);
    }

}

//Erase function used by decide_run() to erase a process
void os::erase() {
    PCB * temp;
    for (list<PCB *>::iterator it = jobs.begin(); it != jobs.end(); it++) {
        temp = *it;
        if(running ->pname == temp -> pname) {
            jobs.erase(it);
        return;
        }
    }
}

void os::decide_wq() {
    if (waitQ.empty()) {
        return;
    }
    else {
        io();
    }
}

//A helper function for the decide_wq function
void os::io() {
    PCB * temp = waitQ.front();
    temp -> waitclk += (machine.vm_clk - running -> before_wq);
    waitQ.pop();
    if (running -> sr.status.r_status == 6) {
        temp -> in >> temp -> read;
        temp -> waitclk += 27;
    }
    else if (running -> sr.status.r_status == 7) {
        temp -> write = temp -> registers[temp -> sr.status.io_reg];
        temp -> waitclk += 27;
    }
    temp -> before_rq = machine.vm_clk;
    readyQ.push(temp);
}

void os::decide_rq() {
    if (readyQ.empty()) {
        return;
    }
    else {
        readyQ.pop();
        if (readyQ.empty()) {
            return;
        }
        else {
            running = readyQ.front();
            running -> readyclk += (machine.vm_clk - (running -> before_rq));//Getting the clock for the wait times
        }
    }
}


/*********************************************************************
The os will now assemble all of the instructions. These will be saved 
into the corresponding .o files. 
**********************************************************************/
void os::assemble() {
    for (int i = 0; i < assembled.size(); i++) {
        assembled[i]->parse();
    }
}

/*********************************************************************
Instrcutions shall now be loaded by the the os on to the VM the os 
will also fill the ready queue with all processes and give the PCB the
info that is needed for initialization.
*********************************************************************/
void os::load() {
    for (list<PCB *>::iterator it = jobs.begin(); it != jobs.end(); ++it) {
        running = *it;
        readyQ.push(*it);
        fstream * temp = &running -> o;
        machine.mem_load(temp);
        running -> base = machine.base;
        running -> limit = machine.limit;
        running -> pc = running -> base;
    }
    machine.underflow = machine.pc;
    machine.pc = 0;
    running = readyQ.front();
}


/************************************************************************
Used to print out the system information so that the user know what was 
done by the OS.
*************************************************************************/
void os::print() {
    fstream sysout;
    sysout.open("system.out", fstream::out);
    sysout << "The system time is " << contextclk + idleclk << " clock ticks.\n";
    sysout << "The system CPU Utilization is " << (float(machine.vm_clk) + float(contextclk))/(float(contextclk) + float(machine.vm_clk) + float(idleclk)) * 100 << " percent.\n";
    sysout << "The system User Utilization is " << float(machine.vm_clk)/(float(contextclk) + float(machine.vm_clk) + float(idleclk)) * 100 << " percent.\n";
    sysout << "Throughput is " << float(psize)/((float(machine.vm_clk) + float(contextclk) + float(idleclk))/1000) << " processes per second.\n";
    sysout.close();
}

/************************************************************************
This is the heart of the os it will handle the running of all processes
it will use the PCB, the VM, the readyQ, and the waitQ. Additionally, it 
will handle any I/O process. The OS will only terminate once all the
processes are finished.
*************************************************************************/
void os::run() {
    while (!jobs.empty()){
        machine.change(&(running -> in), &(running -> o), &(running -> st), &(running -> out), running -> pc, running -> sr.instr, 
        running -> sp, running-> base, running -> limit, running -> processclk, running -> stack, running -> registers); 
        machine.parse(running -> read, running -> write);
        running -> modify(machine.r, machine.sr, machine.pc, machine.sp, machine.clk, machine.max_sp);
        decide();   
    }
    print();
}
