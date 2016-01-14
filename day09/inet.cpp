#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	const char* addr = "192.168.0.106";

	// in_addr_t ip_n1 = inet_addr(addr);
	// printf("%u\n", ip_n1);

	// in_addr_t ip_n2 = inet_network(addr);
	// printf("%u\n", ip_n2);

	in_addr ip_s1;
	int r = inet_aton(addr, &ip_s1);
	printf("%u\n", ip_s1.s_addr);

	in_addr ss;
	ss.s_addr = 192 << 24 | 168 << 16 | 0 << 8 | 26;
	char* s_addr = inet_ntoa(ss);
	printf("%s\n", s_addr);

	return 0;
}