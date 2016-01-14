#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		printf("socket error\n");
		exit(-1);
	}

	sockaddr_in ad;
	ad.sin_family = AF_INET;
	ad.sin_port = htons(11111);
	inet_aton("192.168.0.106", &ad.sin_addr);

	// int r = connect(fd, (sockaddr*)&ad, sizeof(ad));
	// if (r == -1) {
	// 	printf("connect error\n");
	// 	exit(-1);
	// }

	// const char* str = "Hello World!!!";
	// write(fd, str, strlen(str));

	string str;
	while (cin >> str) {
		int r = sendto(fd, str.c_str(), str.size(), 0, (sockaddr*)&ad, sizeof(ad));
		if (r == -1)
			break;

		// 为什么这里没有显式bind也能接收数据？？？
		// 应该是这样的，首先要理解bind的含义
		// 当系统接收到数据时，会根据端口号来分发数据，bing的意义是告诉系统、告诉网络，我这个进程是接收指定ip和指定端口号的。
		// 上面sendto的时候，我们没有显式connect，那么系统就会自动分配一个端口号。就等同于bind了一次。
		// 应该其他程序可以根据系统自动分配的ip和端口号，来发送数据
		char buf[100] = {0};
		recv(fd, buf, sizeof(buf), 0);
		printf("返回的数据：%s\n", buf);
	}

	close(fd);

	return 0;
}
