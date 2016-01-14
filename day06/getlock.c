#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd;
	struct flock lk = {0};

	fd = open("a.txt", O_RDWR);

	int r = fcntl(fd, F_GETLK, &lk);
	if (r == 0)
		printf("得到锁成功\n");
	if (lk.l_type == F_WRLCK)
		printf("写锁!\n");
	printf("start: %lld, len: %lld\n", lk.l_start, lk.l_len);
	return 0;
}