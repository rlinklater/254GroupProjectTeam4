
all: Source.o hexString.o Command.o 
	g++ Source.o hexString.o Command.o -std=c++11 -o a.out

Source.o: Source.cpp hexString.h Command.h
	g++ -std=c++11 -c Source.cpp

hexString.o: hexString.cpp
	g++ -std=c++11 -c hexString.cpp

Command.o: Command.cpp hexString.h
	g++ -std=c++11 -c Command.cpp

clean: 
	rm *o a.out