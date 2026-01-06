#include <iostream>
#include <cmath>
using namespace std;

size_t get_digit(int N)
{
    int count = 1;
    while (N /= 10)
    count++;
    
    return count;
}

int main(void)
{
    int M = 0;
    for (int N = 1; N <= 15; N++)
    {
        M += N + N * pow(10, get_digit(N));
        cout << N << '\n' << M << endl;
    }
}
