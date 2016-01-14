// #include <stdio.h>
#include <iostream>

class Input
{
public:
	int inputInt(const std::string &str)
	{
		std::cout << str;
		int input_num;
		std::cin >> input_num;
		return input_num;
	}
};
