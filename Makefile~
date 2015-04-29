
all: Source.o hexString.o Command.o 
	g++ Source.o hexString.o Command.o -lm-std=c++0x -o a.out

hexString.o: Source.cpp hexString.h Command.h
	g++ -lm -std=c++0x -c Source.cpp

Command.o: hexString.cpp
	g++ -lm -std=c++0x -c hexString.cpp

Source.o: Command.cpp hexString.h
	g++ -lm -std=c++0x -c Command.cpp

clean: 
	rm *o a.out
