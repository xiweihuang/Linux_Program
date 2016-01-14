#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

pthread_t t1, t2;

void handle(int s)
{

}

void* r1(void* data)
{
	while (1) 
	{
		pause();
		printf("活动!\n");
	}
	return NULL;
}

void* r2(void* data)
{
	while (1) 
	{
		sleep(1);
		pthread_kill(t1, 10);
	}
	return NULL;
}

int main()
{
	// pause + pthread_kill 的方式
	signal(10, handle);
	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
