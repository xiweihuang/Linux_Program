#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

pthread_t t1, t2;
sigset_t sigs;

void* r1(void* data)
{
	int s;  // 返回的信号
	while (1) 
	{
		// sleep(1);
		sigwait(&sigs, &s);  // 等待一个信号集(可能会有多个不同的信号，s表示返回的是什么信号)
		printf("活动!\n");
	}
	return NULL;
}

void* r2(void* data)
{
	while (1) 
	{
		sleep(1);

		// t1进程须有一个sigwait先于pthread_kill执行，也就是t1进程必须有一个sigwait在等待pthread_kill发的信号
		// 否则如果没有sigwait，那么就会交给进程处理了，那么程序一般来说就会发生中断。
		// 所以，pthread_kill + sigwait 这套同步的处理方式也不够好
		pthread_kill(t1, 10);  
	}
	return NULL;
}

int main()
{
	// 初始化信号集
	sigemptyset(&sigs);
	sigaddset(&sigs, 10);

	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
