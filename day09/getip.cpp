/*****

一、
sethostent(1);
endhostent();

hostent* ent = gethostbyname(...);

struct  hostent {
             char    *h_name;        // official name of host
             char    **h_aliases;    // alias list
             int     h_addrtype;     // host address type
             int     h_length;       // length of address
             char    **h_addr_list;  // list of addresses from name server
     };

二、
	getprotoent()

	getprotobyname();

*****/

#include <stdio.h>
#include <netdb.h>

// 获取指定域名的ip地址
void test1()
{
	hostent* ent;
	ent = gethostbyname("www.baidu.com");
	// printf("%s\n", ent->h_aliases[0]);

	printf("%hhu.%hhu.%hhu.%hhu\n", ent->h_addr[0], ent->h_addr[1], ent->h_addr[2], ent->h_addr[3]);
}

void test2()
{
	// 打开主机配置数据库文件
	sethostent(1);

	hostent* ent;
	while (1) {
		ent = gethostent();
		if (ent) {
			printf("主机名:%s\n", ent->h_name);
			printf("ip地址:%hhu.%hhu.%hhu.%hhu\n", ent->h_addr[0], ent->h_addr[1], ent->h_addr[2], ent->h_addr[3]);
		} else {
			break;
		}
	}

	// 关闭
	endhostent();
}

void test3()
{
	protoent* ent = getprotobyname("udp");
	printf("%d\n", ent->p_proto);
}

int main()
{
	// test1();
	// test2();
	test3();
	return 0;
}
