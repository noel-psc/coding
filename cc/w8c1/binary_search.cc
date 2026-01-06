#include <iostream>
#define MAX 256
using namespace std;

template <typename T>
int binary_search(T arr[], int len, T target)
{
	int begin = 0, end = len-1;
	while (begin <= end)
	{
		int mid = (begin + end) / 2;
		if (arr[mid] > target) end = mid-1;
		else if (arr[mid] < target) begin = mid+1;
		else return mid;
		// cout << "begin" << begin << "end" << end << "mid" << mid << endl;
	}
	return -1;
}


int main(void)
{
	double arr[MAX] = {};
	int len = 0;
	for (len = 0; len < MAX && cin >> arr[len]; len++) ;
	cin.clear();
	cin.ignore(10000, '\n');
	double target = 0;
	cin >> target;
	int index = binary_search(arr, len, target);
	cout << index << endl;
}
