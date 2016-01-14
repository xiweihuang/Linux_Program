#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	// int r;
	// printf("%d\n", getpid());
	// r = system("./test");
	// printf("%d\n", WEXITSTATUS(r));

	int r = system("ls -l xxx");
	printf("%d\n", WEXITSTATUS(r));

	return 0;
}
