#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a = malloc(4);
	*a = 999;
	printf("%p\n", a);
	while (1);
	return 0;
}