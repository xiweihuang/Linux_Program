/*****
	发送数据

*****/

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <string.h>

int main()
{
	// 1.建立socket
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);

	// 2.连接到指定的地址
	struct sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_path, "my.sock", strlen("my.sock"));

	int r = connect(fd, (struct sockaddr*)&addr, sizeof(addr));  // connect和bind的用法基本一样
	if (r == -1) {
		printf("connect error\n");
		exit(-1);
	}

	// 3.发送数据
	const char* ch = "Hello!Maomaochong!";
	write(fd, ch, strlen(ch));

	// 4.关闭
	close(fd);
	// unlink("my.sock");
	return 0;
}