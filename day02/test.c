#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int main()
{
	int a = 10;
	int b = 20;
	int s = add(a, b);
	printf("%d\n", s);
	return 0;
}