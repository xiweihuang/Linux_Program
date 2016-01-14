/*
【综合案例】
	建立两个子进程：
	子进程1：负责计算1-5000的素数
	子进程2：负责计算5001-10000的素数
	父进程负责存储
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int idx = 0;
int fddata;
void handle(int s)
{
	int status;
	if (s == SIGCHLD) {
		wait(&status);
		if (++idx == 2) {
			close(fddata);
			exit(-1);
		}
	}
}

int isPrime(int num)
{
	int max = num / 2;
	for (int i = 2; i <= max; ++i) {
		if (num % i == 0)
			return 0;
	}
	return 1;
}

int main()
{
	int a[2] = {2, 5001};
	int b[2] = {5000, 10000};

	signal(SIGCHLD, handle);

	// 建立管道
	int fd[2];
	pipe(fd);

	// 这里创建的子进程有严重问题，要理解“子进程是拷贝父进程代码”的，那么子进程也还要跑循环创建进程的
	// 不过！！！如果后面有加exit(0)，那么就等于说子进程执行完这部分代码后，就直接退出了，也相当于退出循环（不会再执行循环），所以效果上没什么问题
	for (int i = 0; i < 2; ++i) {
		if (fork() == 0) {
			close(fd[0]);

			printf("子进程啊子进程\n");

			// 判断素数
			for (int n = a[i]; n <= b[i]; ++n) {
				if (isPrime(n)) {
					write(fd[1], &n, sizeof(int));
				}
			}
			exit(0);

		}
	}

	close(fd[1]);
	int re;
	char buf[20];
	fddata = open("result.txt", O_RDWR|O_CREAT, 0666);
	while (1) {
		read(fd[0], &re, sizeof(int));
		sprintf(buf, "%d\n", re);
		write(fddata, buf, strlen(buf));
	}

	return 0;
}