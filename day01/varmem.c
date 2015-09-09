#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a1 = 10;
	int a2 = 20;
	int a3 = 30;

	int *p1 = malloc(4);
	int *p2 = malloc(4);
	int *p3 = malloc(4);

	printf("%p\n", &a1);
	printf("%p\n", &a2);
	printf("%p\n", &a3);

	printf("\n");

	printf("%p\n", p1);
	printf("%p\n", p2);
	printf("%p\n", p3);

	return 0;
}