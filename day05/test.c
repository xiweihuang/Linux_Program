#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("%d\n", getpid());
	sleep(10);
	return 99;
}