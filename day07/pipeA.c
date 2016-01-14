#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>

int fd;

void end()
{
	close(fd);
	unlink("my.pipe");
	exit(-1);
}

int main()
{
	// 建立管道
	// 打开管道
	// 写数据
	// 关闭管道
	// 删除管道
	signal(SIGINT, end);

	mkfifo("my.pipe", 0666);
	fd = open("my.pipe", O_RDWR);
	int i = 0;
	while (1) {
		write(fd, &i, 4);
		sleep(1);
		++i;
	}

	return 0;
}