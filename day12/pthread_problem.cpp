#include <stdio.h>
#include <pthread.h>

int a = 0, b = 0;

pthread_mutex_t m;  // 1.定义互斥量

void display()
{
	pthread_mutex_lock(&m);
	a++;
	b++;
	if (a != b) {
		printf("%d != %d\n", a, b);
		a = 0;
		b = 0;
	}
	pthread_mutex_unlock(&m);
}

void* run1(void* data)
{
	while (1) {
		display();
	}
	return NULL;
}

void* run2(void* data)
{
	while (1) {
		display();
	}
	return NULL;
}

int main()
{
	pthread_t t1, t2;

	pthread_mutex_init(&m, NULL);  // 2.初始化互斥量

	pthread_create(&t1, NULL, run1, NULL);
	pthread_create(&t2, NULL, run2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&m);  // 4.释放互斥量
	return 0;
}
