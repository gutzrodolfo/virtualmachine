make: Assembler.o VirtualMachine.o os.o PCB.o
	g++ -o os VirtualMachine.o Assembler.o PCB.o os.o main.cpp

Assembler.o: Assembler.cpp
	g++ -c Assembler.cpp

VirtualMachine.o: VirtualMachine.cpp
	g++ -c VirtualMachine.cpp

PCB.o: PCB.cpp
	g++ -c PCB.cpp

os.o: os.cpp
	g++ -c os.cpp

run: 
	./os

clean:
	rm *.o