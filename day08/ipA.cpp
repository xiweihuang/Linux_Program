#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>  // 把ip地址转成整数
#include <string.h>

int main()
{
	// 1.建立socket
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		printf("socket error\n");
		exit(-1);
	}

	// 2.构造本地文件地址
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);  // 主机字节序
	addr.sin_addr.s_addr = inet_addr("192.168.0.106");

	// 3.把socket绑定在地址上
	int r = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		printf("bind error\n");
		exit(-1);
	}
	printf("地址绑定成功\n");

	// 4.接收数据
	char buf[100];
	bzero(buf, sizeof(buf));
	r = read(fd, buf, sizeof(buf));  // >0:成功  -1:失败  0:连接通道关闭了
	printf("%s\n", buf);

	// 5.关闭描述符
	close(fd);

	// 6.删除socket文件
	// unlink("my.sock");

	return 0;
}
