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

	int r = connect(fd, (sockaddr*)&addr, sizeof(addr));
	if (r == -1) {
		printf("connect error\n");
		exit(-1);
	}

	const char* str = "Hello World!!!";
	write(fd, str, strlen(str));

	close(fd);
	
	return 0;
}