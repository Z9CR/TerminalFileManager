TerminalFileManager : main.o commands.o config.o operations.o
	g++ main.o commands.o config.o operations.o -o ./build/TerminalFileManager
	rm -rf *.o

main.o : ./src/main.cpp
	g++ -c ./src/main.cpp

commands.o : ./src/impl/commands.cpp
	g++ -c ./src/impl/commands.cpp

config.o : ./src/impl/config.cpp
	g++ -c ./src/impl/config.cpp

operations.o : ./src/impl/operations.cpp
	g++ -c ./src/impl/operations.cpp

clean : # clean .o File
	rm -rf *.o ./build/TerminalFileManager

run : 
	./build/TerminalFileManager
