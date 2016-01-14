#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* run(void* data)
{
	// while (1) {
		printf("run线程！\n");
	// }
	return NULL;
}

void test1()
{
	pthread_t tid;
	pthread_create(&tid, NULL, run, NULL);  // 创建不会马上就运行，主线程还会继续跑剩下的时间片

	// while (1) {
		printf("main...\n");
	// }
	pthread_join(tid, NULL);  // pthread_join是一个阻塞函数！！！
}

void* thread1(void* data)
{
	while (1) {
		printf("线程1\n");
		// return "Hello World";
		// pthread_exit("Hello World");
		sched_yield();
	}
	// const char* str = "Hello World";
	// return "Hello World";
	return NULL;
}

void* thread2(void* data)
{
	while (1) {
		printf("线程2\n");
		sched_yield();
	}
	return NULL;
}

void test2()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread1, NULL);
	pthread_create(&tid2, NULL, thread2, NULL);

	while (1) {
		printf("主线程\n");
		sched_yield();
	}

	// char* str;
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("%s\n", str);
}

int main()
{
	// test1();
	test2();
	return 0;
}
