/**********************************************
Phase 2 Project
Groupmates: Eli Gonzalez & Rodolfo Gutierrez
Date:       04/21/2014
Class:      CSE 460 

os.cpp
**********************************************/

#include "os.h"
#include <unistd.h> 
#include <stdlib.h> 

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
    psize = jobs.size(); contextclk = 0; finalclk = 0; useclk = 0;
    idle = static_cast<long double> ( time(NULL) );
    as.close();
    VirtualMachine machine;
}

void os::decide() {
    contextclk += 5;
    decide_run();
    decide_wq();              
    decide_rq();        
}

void os::decide_run() {
    if (machine.sr.status.r_status == 1) {
        running -> turntime = machine.endtimestamp - machine.timestamp;
        useclk += running -> processclk;
        running -> print();
        erase();
    }
    else if (machine.sr.status.r_status == 6 or machine.sr.status.r_status == 7) {
        running -> wait_time  = static_cast<long double> ( time(NULL) ); 
        waitQ.push(running); 
    }
    else {
        readyQ.push(running);
        running -> ready_time = static_cast<long double> ( time(NULL) );
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

void os::io() {
    PCB * temp = waitQ.front();
    temp -> wait_time = static_cast<long double> ( time(NULL) ) - temp -> wait_time;
    temp -> waitclk += 1000 * temp -> wait_time; 
    waitQ.pop();
    if (running -> sr.status.r_status == 6) {
        temp -> in >> temp -> read;
    }
    else if (running -> sr.status.r_status == 7) {
        temp -> write = temp -> registers[temp -> sr.status.io_reg];
    }
    temp -> ready_time = static_cast<long double> ( time(NULL) ); 
    readyQ.push(temp);
}

void os::decide_rq() {
    if (readyQ.empty()) {
        return;
    }
    else {
        running -> ready_time = static_cast<long double> (time(NULL) ) - running -> ready_time;
        running -> readyclk += 1000 * running -> ready_time; 
        readyQ.pop();
        if (readyQ.empty()) {
            return;
        }
        else {
            running = readyQ.front();
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
    machine.pc = 0;
    running = readyQ.front();
}


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

void os::timing() {
    idle = static_cast<long double> ( time(NULL) ) - idle;
    idle -= nonidle;
    systime = idle + (contextclk/1000.0);
    finalclk = useclk + (idle * 1000.0) + contextclk;
    cpu_util = (finalclk - (idle * 1000.0))/finalclk * 100.0;
    use_util = useclk/finalclk;
    throughput = (idle + nonidle)/float(psize);
}

void os::print() {
    fstream sysout; 
    sysout.open("system.out", fstream::out); 
    sysout << "The system time is " << systime << " seconds." << endl;
    sysout << "The System CPU Utilization is " << cpu_util << " percent." << endl;
    sysout << "The User CPU Utilization is " << use_util << endl;
    sysout << "The throughput is " << throughput << " processes per second." << endl;
}

/************************************************************************
This is the heart of the os it will handle the running of all processes
it will use the PCB, the VM, the readyQ, and the waitQ. Additionally, it 
will handle any I/O process. The OS will only terminate once all the
processes are finished.
*************************************************************************/
void os::run() {
    while (!jobs.empty()){
        if (running -> sr.status.r_status == 6) {
            machine.read_helper(running -> read);
            running -> waitclk += 27;
            machine.sr.status.r_status = 0;
        }
        if (running -> sr.status.r_status == 7) {
            machine.write_helper(running -> write);
            running -> waitclk += 27;
            machine.sr.status.r_status = 0;
        }
        long double startp = static_cast<long double> ( time(NULL) ); 
        machine.parse();
        nonidle += (static_cast<long double> ( time(NULL) ) - startp);
        running -> modify(machine.r, machine.sr, machine.pc, machine.sp, machine.clk, machine.max_sp);
        decide();
        machine.change(&(running -> in), &(running -> o), &(running -> st), &(running -> out), running -> pc, running -> sr.instr, 
        running -> sp, running-> base, running -> limit, running -> processclk, running -> stack, running -> registers);   
        machine.stack_load();     
    }
    timing();
    print();
}
