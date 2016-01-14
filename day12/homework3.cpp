/*
	这其实是多线程中著名的生产者-消费者模式
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int p_num = 0;

pthread_t t1, t2;
pthread_mutex_t mutex;
pthread_cond_t cond_set, cond_save;

bool isPrime(int num)
{
	int n = num / 2;
	for (int i = 2; i <= n; ++i) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

void setPrimeNumAndSignal(int i)
{
	pthread_mutex_lock(&mutex);
	if (p_num != 0)
		pthread_cond_wait(&cond_set, &mutex);
	p_num = i;
	pthread_cond_signal(&cond_save);
	pthread_mutex_unlock(&mutex);
}

void* findPrimeNumber(void* data)
{
	for (int i = 2; i < 10000; ++i) {
		if (isPrime(i)) {
			setPrimeNumAndSignal(i);
		}
	}
	setPrimeNumAndSignal(-1);
	return NULL;
}

void* savePrimeNumberToDoc(void* data)
{
	int fd = open("prime_num.txt", O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	while (1) {
		int temp;
		
		pthread_mutex_lock(&mutex);
		if (p_num == 0)
			pthread_cond_wait(&cond_save, &mutex);

		if (p_num == -1) {
			pthread_mutex_unlock(&mutex);
			break;
		} else {
			char buf[10];
			int r = sprintf(buf, "%d\n", p_num);
			buf[r] = '\0';
			write(fd, buf, r);
			p_num = 0;  // 这步很关键
			pthread_cond_signal(&cond_set);
			pthread_mutex_unlock(&mutex);
			
		}
	}
	close(fd);
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_set, NULL);
	pthread_cond_init(&cond_save, NULL);

	pthread_create(&t1, NULL, findPrimeNumber, NULL);
	pthread_create(&t2, NULL, savePrimeNumberToDoc, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_cond_destroy(&cond_save);
	pthread_cond_destroy(&cond_set);
	pthread_mutex_destroy(&mutex);
	return 0;
}