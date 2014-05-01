make: Assembler.o VirtualMachine.o os.o
	g++ -o os VirtualMachine.o Assembler.o os.o main.cpp

Assembler.o: Assembler.cpp
	g++ -c Assembler.cpp

VirtualMachine.o: VirtualMachine.cpp
	g++ -c VirtualMachine.cpp

os.o: os.cpp
	g++ -c os.cpp

run: 
	./os

clean:
	rm *.o