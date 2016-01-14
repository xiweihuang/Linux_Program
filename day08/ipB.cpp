#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	// 1.建立socket
	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	// 2.连接到指定的地址
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = inet_addr("192.168.0.106");

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