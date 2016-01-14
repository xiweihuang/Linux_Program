/*****

int socket(int domain, int type, int protocol);
	返回值：成功返回文件描述符号，失败返回-1
	domain：地址族的类型  AF_UNIX       AF_INET
	type：支持的数据格式  SOCK_STREAM   SOCK_DGRAM
	protocol：支持的协议（0为默认的协议），一般建议为0即可

绑定socket在地址（文件、网卡）URL

struct sockaddr;
struct sockaddr_un;   un == unix
struct sockaddr_in;   in == internet

int bind(int fd, struct sockaddr* addr, socklen_t size);
	返回值: 0成功  -1失败
	fd:文件描述符
	addr:绑定地址
	size:地址长度  socklen_t即size_t


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
	if (fd == -1) {
		printf("socket error\n");
		exit(-1);
	}

	// 2.构造本地文件地址
	struct sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_path, "my.sock", strlen("my.sock"));

	// 3.把socket绑定在地址上
	int r = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		printf("bind error\n");
		exit(-1);
	}
	printf("地址绑定成功\n");

	// 4.接收数据
	char buf[10];
	bzero(buf, sizeof(buf));
	r = read(fd, buf, sizeof(buf));  // >0:成功  -1:失败  0:连接通道关闭了
	buf[r] = '\0';
	printf("%s\n", buf);

	// 5.关闭描述符
	close(fd);

	// 6.删除socket文件
	unlink("my.sock");

	return 0;
}
