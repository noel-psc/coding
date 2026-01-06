#include <iostream>
using namespace std;

int main(void)
{
	int cj = 75;

	if (cj >= 60)
	{
		if (cj >= 90)
		{
			cout << "成绩优秀" << endl;
		}
		else
		{
			cout << "成绩良好" << endl;
		}
	}
	else
	{
		cout << "不及格" << endl;
	}

	return 0;
}
