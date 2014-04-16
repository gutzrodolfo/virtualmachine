make: Assembler.o test.cpp
	g++ Assembler.o test.cpp

Assembler.o: Assembler.cpp
	g++ -c Assembler.cpp

run: clean
	./a.out

clean:
	rm Assembler.o