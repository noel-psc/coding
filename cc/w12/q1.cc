#include <iostream>
using namespace std;

class Base{
	public:
		void show() {cout << "Base";}
};

class Mid : public Base{
	public:
		void show() {cout << "Mid";}
};

class Derived:public Mid{
	public:
		void show() {cout << "Derived";}
};

int main()
{
	Base *p = new Derived();
	p->show();

}
