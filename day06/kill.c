#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	while (1) {
		kill(1374, SIGKILL);
		sleep(2);
	}
	return 0;
}