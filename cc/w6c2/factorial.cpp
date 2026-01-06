#include <iostream>

long long factorial(long long n)
{
	if (n == 0 || n == 1)
		return 1L;
	else
	{
		long long res = 1;
		res *= n * factorial(n-1);
		return res;
	}
}

int main(void)
{
	long long n = 1;
	std::cin >> n;
	std::cout << factorial(n) << "\n";
}
