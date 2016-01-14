#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	// 创建消息队列
	key_t key = ftok(".", 255);
	if (key == -1)
		printf("ftok err:%m\n"), exit(-1);
	int msgid = msgget(key, IPC_CREAT|IPC_EXCL|0666);
	if (msgid == -1)
		printf("get err:%m\n"), exit(-1);

	// 构造消息

	// 发送消息
	// 删除队列
	return 0;
}
