#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void deal(int s)
{
	int status;
	wait(&status);
	printf("回收中...\n");
	sleep(5);
	printf("回收完毕: %d\n", WEXITSTATUS(status));
}

int main()
{
	if (fork()) {
		// parent
		signal(SIGCHLD, deal);
		while (1) {
			printf("父进程\n");
			sleep(1);
		}

	} else {
		// child
		printf("子进程\n");
		sleep(10);
		printf("子进程退出！\n");
		exit(88);
	}

	return 0;
}