#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	// 1.socket    建立服务器的文件描述符缓冲
	// 2.bind      把IP地址与端口设置到文件描述符中
	// 3.listen    负责根据客户连接的不同IP与端口，负责生成对应的文件描述符及其信息
	// 4.accept    一旦listen有新的描述符号产生，则返回。否则，会阻塞。accept其实是一个阻塞函数

	// 1.socket
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverfd == -1) {
		printf("socket error\n");
		exit(-1);
	}
	printf("建立服务器socket成功\n");

	// 2.bind
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9999);
	inet_aton("192.168.0.106", &serverAddr.sin_addr);

	int r = bind(serverfd, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (r == -1) {
		printf("bind error\n");
		exit(-1);
	}
	printf("服务器地址绑定成功\n");

	// 3.listen
	r = listen(serverfd, 10);  // 10:排列的队列数(可以认为是最大连接数吗？)
	if (r == -1) {
		printf("listen error\n");
		exit(-1);
	}
	printf("监听服务器成功\n");

	// 4.accept
	sockaddr_in customAddr;
	socklen_t len = sizeof(customAddr);
	int customfd = accept(serverfd, (sockaddr*)&customAddr, &len);  // 这个len的处理必须是这样的！！！
	printf("有人连接：%d, IP:%s:%u\n", customfd, inet_ntoa(customAddr.sin_addr), ntohs(customAddr.sin_port));

	while (1) {
		char buf[1024] = {0};
		int r = recv(customfd, buf, sizeof(buf), 0);
		if (r > 0) {
			printf("%s\n", buf);
		} else if (r == 0) {
			printf("连接断开\n");
			break;
		} else if (r == -1) {
			printf("网络故障\n");
			break;
		}
	}

	close(customfd);
	close(serverfd);



	return 0;
}