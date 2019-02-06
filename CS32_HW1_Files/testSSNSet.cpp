#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	SSNSet s;

	ItemType x = 9876543;
	ItemType y = 3568678;
	ItemType z = 2345457;
	ItemType i = 5686789;
	ItemType j = 1465675;
	
	//test adding and printing
	assert(s.add(x));
	cout << "*****" << endl;
	s.print();
	assert(s.add(y));
	cout << "*****" << endl;
	s.print();
	assert(s.add(z));
	cout << "*****" << endl;
	s.print();
	assert(s.add(i));
	cout << "*****" << endl;
	s.print();
	assert(s.add(j));
	cout << "*****" << endl;
	s.print();

	//test size function
	cout << "size: " << s.size() << endl;

	cout << "Passed all tests" << endl;
}