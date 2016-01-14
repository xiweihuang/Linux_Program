#include <stdio.h>

int inputInt(const char *info);
void diamond(int r);

int main()
{
	int r = inputInt("please input the radius: ");
	diamond(r);
	return 0;
}
