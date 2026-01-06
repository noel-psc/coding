#include <iostream>
using namespace std;

class Base{
	public:
	virtual void f(int x) {cout << "Base";}
};

class Derived : public Base{
	public:
		void f(double x) {cout << "Derived";}
};

int main()
{
	Base *p = new Derived();
	p->f(10);
}
