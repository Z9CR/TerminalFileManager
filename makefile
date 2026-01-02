TerminalFileManager : main.o commands.o
	g++ main.o commands.o -o ./build/TerminalFileManager
	rm -rf *.o

main.o : ./src/main.cpp
	g++ -c ./src/main.cpp

commands.o : ./src/impl/commands.cpp
	g++ -c ./src/impl/commands.cpp

clean : # clean .o File
	rm -rf *.o ./build/TerminalFileManager

run : 
	./build/TerminalFileManager
