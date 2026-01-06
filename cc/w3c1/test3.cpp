#include <iostream>
using namespace std;

int main(void)
{
	int a = 0;
	cin >> a;
	if ((a % 2 == 1 && a % 3 != 0) || a % 15 == 0)
		cout << "True"<< endl;
	else
		cout << "False" << endl;

	int n = 0;
	cout << "10-20" << endl;
	cin >> n;
	if (n >= 10 & n <= 20)
		cout << "true" << endl;
	else
		cout << "false" << endl;


	return 0;
}
