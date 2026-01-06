#include <iostream>
#include <string>
#define NS 3
using namespace std;

class Student
{
	private:
		string sID = "";
		string sName = "";
		float fScores[NS] = {};
	public:
		Student();
		Student(string sID, string sName, float fScores[NS]);
}

int main(void)
{

}
