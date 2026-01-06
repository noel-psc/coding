#include <iostream>
using namespace std;

template <typename T>
int exchange(T *a, T *b)
{
	swap (*a, *b);
	return 0;
}

int main(void)
{
	int a = 1, b = 100;
	cout << a << ' ' << b << endl;
	exchange(&a, &b);
	cout << a << ' ' << b << endl;

}
