#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

pthread_t t1, t2;

// 1.定义条件量
pthread_cond_t cond;

pthread_mutex_t mutex;

void* r1(void* data)
{
	while (1) 
	{
		// 第二个参数是加一个互斥量，为什么要加互斥量？
		pthread_cond_wait(&cond, &mutex);
		printf("活动!\n");
	}
	return NULL;
}

void* r2(void* data)
{
	while (1) 
	{
		// sleep(1);
		// 信号量没有累计，也类似互斥量，只有两种状态
		pthread_cond_signal(&cond);
		pthread_cond_signal(&cond);
		// pthread_cond_signal(&cond);
		sleep(5);
	}
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex, NULL);

	// 2.初始化条件量
	pthread_cond_init(&cond, NULL);

	pthread_create(&t1, NULL, r1, NULL);
	pthread_create(&t2, NULL, r2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	// 2.释放条件量
	pthread_cond_destroy(&cond);

	pthread_mutex_destroy(&mutex);
	return 0;
}
