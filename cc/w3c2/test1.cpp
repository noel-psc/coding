#include <iostream>
using namespace std;

void swap_(void* a, void* b)
{
	

	return;
}

int main(void)
{
	float a, b, t;
	cin >> a >> b;
	if (a > b)
	{
		t = a;
		a = b;
		b = t;
	}
	swap(a, b); 
	cout << a << b << endl;

	return 0;
}
