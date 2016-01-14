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
	exit(-1);
}

int main()
{
	// 打开管道
	// 写数据
	// 关闭管道
	// 删除管道
	signal(SIGINT, end);
	fd = open("my.pipe", O_RDWR);
	int i = 0;
	while (1) {
		read(fd, &i, 4);
		printf("%d\n", i);
	}

	return 0;
}