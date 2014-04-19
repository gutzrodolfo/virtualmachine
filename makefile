make: Assembler.o VirtualMachine.o
	g++ -o Assembler Assembler.o test.cpp
	g++ -o VM VirtualMachine.o TestVM.cpp

Assembler.o: Assembler.cpp
	g++ -c Assembler.cpp

VirtualMachine.o: VirtualMachine.cpp
	g++ -c VirtualMachine.cpp

run: 
	./Assembler
	./VM

clean:
	rm Assembler.o
	rm VirtualMachine.o