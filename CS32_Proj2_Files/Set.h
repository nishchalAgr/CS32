#ifndef SETINCLUDED
#define SETINCLUDED

#include <string>

using ItemType = int;

class Set
{
public:
	Set();
	~Set();
	Set(const Set& other);
	Set& operator=(const Set& other);
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
	void dump();

private:

	struct node {

		ItemType value;

		node* next;
		node* prev;

	};

	node* head;

	int m_size;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);
void swapItems(ItemType& a, ItemType& b);
void emptyList(Set& empty);

#endif

