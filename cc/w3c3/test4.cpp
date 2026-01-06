#include <iostream>
using namespace std;

int main(void)
{
	int a, b, max;
	cout << "请输入a, b: ";
	cin >> a >> b;

/*	if (a > b)
		max = a;
	else
		max = b;
*/
	max = a > b ? a : b;
	cout << "最大的是" << max << endl;

	return 0;
}
