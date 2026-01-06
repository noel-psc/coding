#include <iostream>
using namespace std;

class C
{
	private:
		int a;
	public:
		C(int a)
		{
			this->a = a;
		}
		void put()
		{
			cout << a << endl;
		}
};

int main()
{
	C c(1);
	c.put();
}
