turing:TuringMachine.o TuringMachine.h main.o
	g++ TuringMachine.o main.o TuringMachine.h -o turing
main.o:main.cpp
	g++ -c main.cpp -o main.o
TuringMachine.o:TuringMachine.cpp 
	g++ -c TuringMachine.cpp -o TuringMachine.o
clean:
	rm *.o
	rm turing
