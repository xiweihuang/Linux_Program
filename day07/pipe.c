#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	pipe(fd);
	if (fork()) {
		// parent 只写数据，所以把读的文件描述符关闭
		close(fd[0]);
		while (1) {
			write(fd[1], "Hello", 5);
			sleep(1);
		}
	} else {
		// child 只读数据
		close(fd[1]);
		char buf[20];
		while (1) {
			int r = read(fd[0], buf, 20);
			buf[r] = '\0';
			printf("%s\n", buf);
		}
	}

	return 0;
}