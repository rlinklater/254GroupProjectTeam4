
all: Source.o hexString.o Command.o 
	g++ Source.o hexString.o Command.o -std=c++0x -o a.out

Source.o: Source.cpp hexString.h Command.h
	g++ -std=c++0x -c Source.cpp

hexString.o: hexString.cpp
	g++ -std=c++0x -c hexString.cpp

Command.o: Command.cpp hexString.h
	g++ -std=c++0x -c Command.cpp

clean: 
	rm *o a.out
