TerminalFileManager : main.o commands.o FileSystem.o
	g++ main.o commands.o FileSystem.o -o ./build/TerminalFileManager
	rm -rf *.o

main.o : ./src/main.cpp
	g++ -c ./src/main.cpp

commands.o : ./src/impl/commands.cpp
	g++ -c ./src/impl/commands.cpp

FileSystem.o : ./src/impl/FileSystem.cpp
	g++ -c ./src/impl/FileSystem.cpp

clean : # clean .o File
	rm -rf *.o ./build/TerminalFileManager

run : 
	./build/TerminalFileManager