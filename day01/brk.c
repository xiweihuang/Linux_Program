#include <stdio.h>
#include <unistd.h>

int main()
{
	// int *p1 = sbrk(4);
	// int *p2 = sbrk(0);
	// int *p3 = sbrk(200);
	// int *p4 = sbrk(1);

	// printf("%p\n", p1);
	// printf("%p\n", p2);
	// printf("%p\n", p3);
	// printf("%p\n", p4);

	int *p = sbrk(0);
	brk(p+1);
	// *p = 800;
	printf("%p\n", p);
	printf("%p\n", sbrk(0));

	return 0;
}
