  //  #include "newSet.h"
  //  #include <iostream>
  //  #include <cassert>
  //  using namespace std;

  //  int main()
  //  {
  //   	Set a(1000);   // a can hold at most 1000 distinct items
  //   	Set b(5);      // b can hold at most 5 distinct items
  //   	Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
  //   	ItemType v[6] = {"h","he","hee","heee","heeee","heeeee"}; //six distinct values of the appropriate type
		//ItemType d[9] = { "s","se" ,"see" ,"seee" ,"seeee" ,"seeeee" ,"seeeeee" ,"seeeeeee" ,"seeeeeeee" };
	 //      // No failures inserting 5 distinct items into b
	 //    for (int k = 0; k < 5; k++) assert(b.insert(v[k]));
		// for (int k = 0; k < 9; k++) assert(c.insert(d[k]));

		// c = b;
		// Set e = b;


		// //b.print();
		// c.print();
		// e.print();
	 //      // Failure if we try to insert a sixth distinct item into b
		// //assert(!b.insert(v[5]));

  //   	 //b.swap(c);

		////b.print();
		////c.print();

	 //	// When two Sets' contents are swapped, their capacities are swapped
  //    	 // as well:
  //   	// a.swap(b);
  //   	 //assert(!a.insert(v[5])  &&  b.insert(v[5]));
		// cout << "passed" << endl;
  //  }

#include "newSet.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "laobing";
	assert(ss.get(0, x) && x == "pita");
	assert(ss.get(1, x) && x == "roti");
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

