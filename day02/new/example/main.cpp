#include <iostream>
// #include <dlfcn.h>
int getInput();
int addNum(int a, int b);

int main()
{
	int a = getInput();
	int b = getInput();
	std::cout << addNum(a, b) << std::endl;
	return 0;
}
