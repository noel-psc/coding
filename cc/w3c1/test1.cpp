#include <iostream>
#include <ctime>
#define MAX 256
using namespace std;

double *bubble_sort(double *arr, int len)
{
	cout << "len: " << len << endl;
	double swap = 0;
	for (int i = 0; i <= len-2; i++) //冒泡排序最多遍历n-1次,从0开算是n-2
	{
		for (int j = 0; j <= len-i-2; j++)
		{
			if (arr[j] > arr[j+1])
			{
				swap = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = swap;
			}
		}
	}

	return arr;
}

int main(void)
{
	clock_t a, b;
	double arr[MAX] = {};
	double tmp = 0;
	int len = 0;
	cout << "请输入数组(输入非数字结束)";
	for (int i = 0; cin >> tmp; i++)
	{
		arr[i] = tmp;
		len = i+1;
	}
	double *sourted_arr = bubble_sort(arr, len);
	a = clock();
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " " ;
	}
	b = clock();
	cout << "耗时" << b - a << endl;

	return 1;
}

