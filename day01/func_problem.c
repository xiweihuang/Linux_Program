#include <stdio.h>

int __attribute__((cdecl)) add(int a, int b)
{
	return a + b;
}

int main()
{
	// int (*fun)(int) = (int(*)(int))add;
	// int r = fun(20);
	// printf("%d\n", r);

	int r = add(10, 20);
	printf("%d\n", r);

	return 0;
}
