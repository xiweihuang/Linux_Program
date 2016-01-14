#include "iot.h"
#include "gra.h"

int main()
{
	Input input;
	Graphic gra;

	int r = input.inputInt("Please input:");
	gra.diamond(r);

	return 0;
}