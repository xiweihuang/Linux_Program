#include <stdio.h>
#include <signal.h>

void deal(int s)
{
	printf("起床\n");
}

int main()
{
	signal(SIGALRM, deal);
	alarm(5);
	while (1) {

	}
	return 0;
}
