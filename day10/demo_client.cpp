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
	// 1.建立socket
	// 2.连接到服务器
	// 3.打开文件
	// 4.发送文件名
	// 5.循环发送数据
	// 6.读取到文件尾，发送一个0长度的数据包，表示文件发送结束
	// 7.关闭文件

	// 1.建立socket
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) {
		printf("socket error\n");
		exit(-1);
	}
	printf("socket成功！\n");

	// 2.连接到服务器
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9988);
	inet_aton("192.168.0.106", &addr.sin_addr);

	int r = connect(sfd, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		close(sfd);
		printf("connect error\n");
		exit(-1);
	}
	printf("connect成功！\n");

	// 3.打开文件
	const string filename = "tcp_server.cpp";
	int ffd = open(filename.c_str(), O_RDONLY);
	if (ffd == -1) {
		close(sfd);
		printf("open file error\n");
		exit(-1);
	}
	printf("打开文件成功\n");

	// 4.发送文件名
	int len = filename.size();
	r = send(sfd, &len, sizeof(len), 0);
	if (r == -1) {
		printf("send file name error\n");
		close(sfd);
		close(ffd);
		exit(-1);
	}

	send(sfd, filename.c_str(), filename.size(), 0);
	printf("发送文件名成功\n");

	char buf[128];
	while (1) {
		int size = read(ffd, buf, 128);
		if (size > 0) {
			send(sfd, &size, sizeof(size), 0);  // 包头
			send(sfd, buf, size, 0);  // 包体
		} else {
			break;
		}
	}

	int size = 0;
	send(sfd, &size, sizeof(size), 0);
	close(ffd);
	close(sfd);
	printf("发送成功\n");

	return 0;
}













