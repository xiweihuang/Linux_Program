#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void exitHandle(void* data)
{
	printf("结束时候的调用！！！\n");
	pthread_mutex_unlock(&mutex);
}

void test()
{
	return;
}

void* runOdd(void* data)
{
	for (int i = 1; ; i+=2) {
		pthread_cleanup_push(exitHandle, NULL);

		pthread_mutex_lock(&mutex);
		sleep(1);
		printf("%d\n", i);
		// return NULL;         // push和pop对中不能直接出现return!!!
		// pthread_exit(NULL);
		// test();  // 这两种都没有问题
		pthread_mutex_unlock(&mutex);

		pthread_cleanup_pop(0);
	}
	return NULL;
}

void* runEven(void* data)
{
	for (int i = 0; ; i+=2) {
		pthread_mutex_lock(&mutex);
		sleep(1);
		printf("%d\n", i);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex, NULL);

	pthread_t t_odd, t_even;
	pthread_create(&t_odd, NULL, runOdd, NULL);
	pthread_create(&t_even, NULL, runEven, NULL);

	sleep(5);
	pthread_cancel(t_odd);  // 强制关闭t_odd这个线程，意图造成死锁。并试图解决这种死锁的情况

	pthread_join(t_odd, NULL);
	pthread_join(t_even, NULL);

	pthread_mutex_destroy(&mutex);
	return 0;
}
