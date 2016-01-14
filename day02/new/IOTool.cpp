#include <stdio.h>

int GetInput(const char* info)
{
	int input;
	printf("%s:", info);
	scanf("%d", &input);
	return input;
}