#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	// int *p1 = malloc(4);
	// int *p2 = malloc(4);

	// printf("%p\n", p1);
	// printf("%p\n", p2);

	printf("%d\n", getpid());
	while (1);
	return 0;
}
