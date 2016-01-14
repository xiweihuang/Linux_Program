#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/un.h>

int main()
{
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (fd == -1) {
		printf("socket error\n");
		exit(-1);
	}

	sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_path, "test.sock", strlen("test.sock"));

	int r = bind(fd, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		printf("bind error\n");
		exit(-1);
	}

	char buf[200];
	bzero(buf, sizeof(buf));
	r = read(fd, buf, sizeof(buf));
	printf("%s\n", buf);

	close(fd);
	unlink("test.sock");

	return 0;
}
