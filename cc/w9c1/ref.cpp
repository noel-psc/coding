#include <iostream>

using namespace std;

template<typename T>
void my_swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

int main(void)
{
	int a = 0, b = 1;
	cout << a << ' ' << b << endl;
	my_swap(a, b);
	cout << a << ' ' << b << endl;
}
