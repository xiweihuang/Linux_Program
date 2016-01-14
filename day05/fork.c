#include <stdio.h>
#include <unistd.h>

int main()
{
	// int pid;
	// printf("创建进程前！\n");
	// pid = fork();
	// printf("创建进程后: %d\n", pid);

	int pid = fork();
	if (pid == 0) {
		while (1) {
			printf("子进程\n");
			sleep(1);
		}
	} else {
		while (1) {
			printf("父进程\n");
			sleep(1);
		}
	}
	return 0;
}
