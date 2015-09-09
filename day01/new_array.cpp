#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main()
{
	// int *p1 = new int[4]();
	// int *p2 = new int[4]();

	// *(p1+4) = 100;

	// printf("%d\n", *p2);

	// printf("%p\n", p1);
	// printf("%p\n", p2);


	int *p1 = static_cast<int*>(calloc(4, 4));
	int *p2 = static_cast<int*>(calloc(4, 4));

	printf("%p\n", p1);
	printf("%p\n", p2);


	// // printf("%d\n", p[2]);
	// printf("%p\n", p);
	// printf("%p\n", p+1);

	// *(p+2) = 20;
	// printf("%d\n", p[2]);

	// // printf("%p\n", &(p[2]));


	// int *p1 = new int;
	// int *p2 = new int;
	// printf("%p\n", p1);
	// printf("%p\n", p2);

	// *p1 = 10;
	// *p2 = 20;

	// *(p1+4) = 30;

	// printf("%d\n", *p2);

	return 0;
}