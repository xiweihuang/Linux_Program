#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle(int s)
{
	printf("我是信号发生！\n");
	// sleep(5);
}

int main()
{
	signal(SIGINT, handle);
	while (1) {
		printf("进程在执行！%d\n", getpid());
		sleep(1);
	}
	return 0;
}