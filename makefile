final: dir_help.o
	g++ -o test dir_help.o
dir_help.o: dir_help.cpp
	g++ -c dir_help.cpp
