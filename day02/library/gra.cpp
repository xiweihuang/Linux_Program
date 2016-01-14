#include <iostream>

class Graphic
{
public:
	void diamond(int r)
	{
		for (int y = 0; y <= 2*r; ++y) {
			for (int x = 0; x <= 2*r; ++x) {
				if (y == -x + r || y == x - r || y == x + r || y == -x + 3 * r) {
					std::cout << "*";
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
	}
};
