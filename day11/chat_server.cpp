#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main()
{
	// 1.建立socket
	// 2.绑定地址与端口
	// 3.监听
	// 4.构造监听的描述符号集合[服务器描述符号，客户描述符号]
	// 5.使用select控制描述符号集合
	//   分两种情况处理：
	//   a.有客户连接:服务器描述符号
	//   b.有客户发送数据:客户描述符号

	int sfd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in dr;
	dr.sin_family = AF_INET;
	dr.sin_port = htons(8866);
	inet_aton("192.168.0.106", &dr.sin_addr);

	bind(sfd, (sockaddr*)&dr, sizeof(dr));
	listen(sfd, 10);

	// 4.
	// 4.1清空
	// 4.2加入服务器描述符号
	// 4.3加入客户描述符号
	int count = 0;
	int maxfd = 0;
	char buf[1024];
	fd_set fds;
	FD_ZERO(&fds);
	int fdall[100];
	for (int i = 0; i < 100; i++) {
		fdall[i] = -1;
	}

	while (1) {
		maxfd = 0;
		FD_ZERO(&fds);
		FD_SET(sfd, &fds); // 加入服务器描述符号
		maxfd = maxfd >= sfd ? maxfd : sfd;
		for (int i = 0; i < count; ++i) {
			if (fdall[i] != -1) {
				FD_SET(fdall[i], &fds);
				maxfd = maxfd >= fdall[i] ? maxfd : fdall[i];
			}
		}

		int r = select(maxfd + 1, &fds, 0, 0, 0);
		if (FD_ISSET(sfd, &fds)) {
			fdall[count] = accept(sfd, 0, 0);
			printf("有客户连接\n");
			++count;
		}
		for (int i = 0; i < count; ++i) {
			// 判定改变描述符号是否存在
			if (fdall[i] != -1 && FD_ISSET(fdall[i], &fds)) {
				// 读取数据
				r = recv(fdall[i], buf, 1023, 0);
				if (r == 0) {
					printf("有客户退出\n");
					close(fdall[i]);
					fdall[i] = -1;
				} else if (r == -1) {
					printf("网络故障\n");
					close(fdall[i]);
					fdall[i] = -1;
				} else {
					// 广播数据
					for (int j = 0; j < count; j++) {
						if (fdall[j] != -1) {
							send(fdall[j], buf, r, 0);
						}
					}
				}
			}
		}
	}



	return 0;
}
