#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	vector<string> vec;
	string str = "tom jack rose";
	size_t pos_beg = 0;
	// size_t pos_end = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == ' ' || i == str.size() - 1) {
			// cout << pos_beg << ", " << i << endl;
			string s(str, pos_beg, i - pos_beg);
			vec.push_back(s);
			pos_beg = i + 1;
		}
	}

	for (const auto& v : vec) {
		cout << v << endl;
	}

	return 0;
}