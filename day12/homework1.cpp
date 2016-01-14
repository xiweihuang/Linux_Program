// 写一个死锁程序

#include <stdio.h>
#include <pthread.h>

pthread_t t1, t2;
pthread_mutex_t mutex1, mutex2;
pthread_cond_t cond;

void* run1(void* data)
{
	while (1) {
		pthread_mutex_lock(&mutex1);
		// pthread_cond_wait(&cond, &mutex2);  // 第二个参数如果不是mutex1这把锁，就会造成死锁
		pthread_cond_wait(&cond, &mutex1);
		printf("线程--1\n");
		pthread_mutex_unlock(&mutex1);
	}
	return NULL;
}

void* run2(void* data)
{
	while (1) {
		pthread_mutex_lock(&mutex1);
		printf("线程--2\n");
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex1);
	}
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_create(&t1, NULL, run1, NULL);
	pthread_create(&t2, NULL, run2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex2);
	pthread_mutex_destroy(&mutex1);

	return 0;
}
