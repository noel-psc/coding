#include <iostream>
#define N 10

using namespace std;

template <typename T>
int bubble_sort(T arr[], size_t len)
{
	for (int i = 0; i < len-1; i++)
	{
		for (int j = 0; j < len-i-1; j++)
		{
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);
		}
	}
	return 0;
}

int main(void)
{
	int grade[N] = {};
	int len = 0;
	for (len = 0; len < N && cin >> grade[len]; len++) ;
	cin.clear();
	cin.ignore(10000, '\n');
	for (int i = 0; i < len; i++)
		cout << grade[i] << ' ';
	bubble_sort(grade, len);
	cout << endl;
	for (int i = 0; i < len; i++)
		cout << grade[i] << ' ';
}
