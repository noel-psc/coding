#include <iostream>
using namespace std;

int main(void)
{
	double x, y;

	cout << "请输入x: ";
	cin >> x;
	if (x < 0)
		y = -1;
	else if (x = 0)
		y = 0;
	else
		y = 1;

	cout << "y = " << y << endl;

	return 0;
}
