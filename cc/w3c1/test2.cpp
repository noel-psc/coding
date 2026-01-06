#include <iostream>
#include <ctime>
using namespace std;

int main(void)
{
	clock_t a, b;
	std::cout << (a = clock()) << endl;
	for (int i = 0; i < 99999; i++)
	{
		i * i;
	}
	cout << ( b = clock()) << endl;
	cout << b - a << endl;

	return 0;
}
