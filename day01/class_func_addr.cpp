#include <stdio.h>
#include <functional>

class Person
{
public:
	void test()
	{
		printf("hello\n");
	}
};

int main()
{
	Person per;
	auto p = &per;
	printf("%p\n", p-16*2);

	auto f = p - 4*8;
	(void(*)())f();

	// auto f = std::bind(&Person::test, per);
	// printf("%p\n", &f);
	return 0;
}
