#include <stdio.h>
#include <unistd.h>

int isPrime(int a)
{
	int i;
	for (i = 2; i < a; ++i) {
		if (a % i == 0)
			return 1;
	}
	return 0;
}

int main()
{
	int *p = sbrk(0);
	int *r = p;
	int i;
	for (i = 2; i < 100; ++i) {
		if (isPrime(i)) {
			brk(r+1);
			*r = i;
			r = sbrk(0);
		}
	}

	r = p;
	// printf("%p\n", r);
	// printf("%p\n", sbrk(0));
	while (r != sbrk(0)) {
		printf("%d\n", *r);
		++r;
	}

	// printf("%d\n", isPrime(4));

	return 0;
}