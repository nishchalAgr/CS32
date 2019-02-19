
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3

int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	//countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);

	if (n2 == 0) return 1;

	else if (n1 == 0) return 0;

	cout << "a1: " << a1[0] << ", a2:" << a2[0] << endl;

	int include;
	int include2;

	//only iterate when we find a match
	if (a1[0] == a2[0]) {
		//include goes to next element in a2
		include = countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		//inlcude2 looks for multiples of the same element in a2
		include2 = countIncludes(a1 + 1, n1 - 1, a2, n2);
		cout << "includes: " << include << "," << include2 << endl;
		return include + include2;

	}

	else return countIncludes(a1 + 1, n1 - 1, a2, n2);


	
}

void divide(double a[], int n, double divider, int& firstNotGreater, int& firstLess)
{
	if (n < 0) n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > divider
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == divider
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < divider

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < divider)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > divider)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{

	if (n < 1) {
	
		return;

	}

	int firstNotGreater = n / 2;
	int firstLess = n / 2 + 1;

	divide(a, n, a[n / 2 - 1], firstNotGreater, firstLess);
	order(a, n / 2);
	order(a + n / 2, n / 2);
}


