demo:
	clang++ -c input.cpp
	clang++ -c add.cpp
	clang++ -shared input.o add.o -olibTools.so
	clang++ main.cpp -lTools -L. -omain
	