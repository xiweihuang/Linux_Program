#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
	int fd = open("tmp", O_RDWR|O_CREAT, 0666);
	ftruncate(fd, 4);
	int* p = mmap(0, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	int i = 0;
	while (1) {
		sleep(1);
		*p = i;
		++i;
	}
	close(fd);

	return 0;
}
