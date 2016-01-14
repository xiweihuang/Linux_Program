#include <stdio.h>

void drawDiamond(int radius)
{
	for (int y = 0; y <= 2*radius; ++y) {
		for (int x = 0; x <= 2*radius; ++x) {
			if (y == -x + radius || y == x - radius || y == -x + 3*radius || y == x + radius) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
	}
}