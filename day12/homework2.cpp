// 写一个程序，两个线程写数据到文件（数据格式：日期时间，线程ID\n）

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

pthread_t t1, t2;
int fd;
pthread_mutex_t writeMutex;

void writeTxt(int tid)
{
	// 获取日期时间
	// 获取线程id
	time_t t;
	time(&t);
	tm* tmp = localtime(&t);

	char buf[100];
	// int r = sprintf(buf, "日期：%02d-%02d-%02d，线程id = %d\n", tmp->tm_hour, tmp->tm_min, tmp->tm_sec, tid);
	int r = sprintf(buf, "日期：%ld，线程id = %d\n", t, tid);
	buf[r] = '\0';

	pthread_mutex_lock(&writeMutex);
	write(fd, buf, r);
	pthread_mutex_unlock(&writeMutex);
}

void* run1(void* data)
{
	for (int i = 0; i < 10000; ++i) {
		writeTxt(1);
	}
	return NULL;
}

void* run2(void* data)
{
	for (int i = 0; i < 10000; ++i) {
		writeTxt(2);
	}
	return NULL;
}

int main()
{
	fd = open("data.txt", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1) {
		printf("open error\n");
		return -1;
	}

	pthread_mutex_init(&writeMutex, NULL);

	pthread_create(&t1, NULL, run1, NULL);
	pthread_create(&t2, NULL, run2, NULL);


	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&writeMutex);

	close(fd);
	return 0;
}
