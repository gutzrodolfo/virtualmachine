make: Assembler.o VirtualMachine.o os.cpp
	g++ -o os VirtualMachine.o Assembler.o os.cpp

Assembler.o: Assembler.cpp
	g++ -c Assembler.cpp

VirtualMachine.o: VirtualMachine.cpp
	g++ -c VirtualMachine.cpp

run: 
	./os prog

clean:
	rm Assembler.o
	rm VirtualMachine.o