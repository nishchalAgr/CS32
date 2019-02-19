
bool anyTrue(const double a[], int n) {

	//if we have finished the array return false
	if (n - 1 < 0) return false;
	
	else if (somePredicate(a[n - 1])) return true;

	anyTrue(a, n - 1);

}

int countTrue(const double a[], int n) {

	int count;

	if (n - 1 < 0) return 0;

	if(somePredicate(a[n - 1])){

		return countTrue(a, n - 1) + 1;
	
	}

	return countTrue(a, n - 1);


}

int firstTrue(const double a[], int n) {

	//if we have finished the array return false
	if (n - 1 < 0) return -1;

	int index = firstTrue(a, n - 1);

	if (somePredicate(a[n - 1])) { 
		
		if (n - 1 < index || index == -1) index = n - 1;

	}

	return index;

}

int positionOfMin(const double a[], int n) {

	if (n == 0) return -1;

	if (n - 1 == 0) return 0;

	int min = positionOfMin(a, n - 1);

	if (a[n - 1] < a[min]) min = n - 1;

	return min;

}


bool includes(const double a1[], int n1, const double a2[], int n2)
{
	bool include;
	bool include2;
	
	//iteration thorugh a1
	if (a1[n1 - 1] == a2[n2 - 1]) { 
		include = true;
		n1 = n1 - 1;
	}

	else if (n1 == 0) include = false;

	else include = includes(a1, n1 - 1, a2, n2);

	//iteration through a2
	if (n2 == 0) include2 = true;
	
	else include2 = includes(a1, n1, a2, n2 - 1);

	//return true if true for all iterations of a2
	return include && include2;
	

}
