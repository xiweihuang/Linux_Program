#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string>
using namespace std;

int main()
{
	// 1.建立服务器socket
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) {
		printf("socket error\n");
		exit(-1);
	}

	// 2.绑定IP地址与端口
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9988);
	inet_aton("192.168.0.106", &addr.sin_addr);

	int r = bind(sfd, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		printf("bind error\n");
		close(sfd);
		exit(-1);
	}

	// 3.监听
	r = listen(sfd, 10);
	if (r == -1) {
		printf("listen error\n");
		close(sfd);
		exit(-1);
	}

	// 4.接收连接
	int cfd = accept(sfd, NULL, NULL);
	if (cfd == -1) {
		printf("accept error\n");
		close(sfd);
		exit(-1);
	}

	// 5.接收文件名
	int len;
	r = recv(cfd, &len, sizeof(len), MSG_WAITALL);
	char filename[len];
	r = recv(cfd, filename, len, MSG_WAITALL);
	filename[len] = '\0';

	// 6.创建文件
	int ffd = open(filename, O_RDWR|O_CREAT, 0666);

	// 7.循环接收文件数据
	while (1) {
		recv(cfd, &len, sizeof(len), MSG_WAITALL);
		if (len == 0)
			break;
		char buf[len];  // 这里应该是动态分配的数组吧，不知道为什么会没问题？？？
		recv(cfd, buf, len, MSG_WAITALL);
		write(ffd, buf, len);
	}

	close(ffd);
	close(cfd);
	close(sfd);
	printf("接收文件完毕\n");

	return 0;
}