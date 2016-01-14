#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		printf("socket error\n");
		exit(-1);
	}

	sockaddr_in ad;
	ad.sin_family = AF_INET;
	ad.sin_port = htons(11111);  // 网络字节序
	inet_aton("192.168.0.106", &ad.sin_addr);  // 自己写的（非用户输入）的，就没必要做异常处理了

	int r = bind(fd, (sockaddr*)&ad, sizeof(ad));
	if (r == -1) {
		printf("bind error\n");
		exit(-1);
	}
	printf("绑定成功\n");
	// int r = 0;

	char buf[100] = {0};
	sockaddr_in ad_snd;
	socklen_t len;
	while (1) {
		len = sizeof(ad_snd);
		r = recvfrom(fd, buf, sizeof(buf) - 1, 0, (sockaddr*)&ad_snd, &len);
		if (r > 0) {
			//success
			buf[r] = 0;
			printf("发送者IP:%s, 数据:%s\n", inet_ntoa(ad_snd.sin_addr), buf);

			sendto(fd, "收到", strlen("收到"), 0, (sockaddr*)&ad_snd, sizeof(ad_snd));

		} else if (r == 0) {
			printf("关闭\n");
			break;
		} else if (r == -1) {
			printf("网络故障\n");
			break;
		}
	}

	close(fd);

	return 0;
}
