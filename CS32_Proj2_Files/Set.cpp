#include "Set.h"
#include <iostream>

Set::Set() {

	head = new node;
	head->next = head;
	head->prev = head;
	m_size = 0;

}

Set::~Set() {

	// makes sure that size is zero
	if (m_size > 0) {

		node* currentNode = head->next;
		node* nextNode;

		while (currentNode != head) {
		
			nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode; 
		
		}

	}

	m_size = 0;
	delete head;

}

//copy constructor
Set::Set(const Set& other)
{
	//initialize head and m_size
	head = new node;
	head->next = nullptr;
	head->prev = nullptr;
	m_size = 0; //m_size will automatically update with insert

	//go through the list of the existing Set and copy each value over to the new Set
	for (node* p = other.head->next; p != other.head; p = p->next) {
		
		this->insert(p->value);

	}
	
}

//assignment operator - copy and swap
Set& Set::operator=(const Set& other) {

	if (this != &other) {
	
		Set temp(other);
		swap(temp);
	
	}

	return *this;

}

bool Set::empty() const {

	return (m_size == 0);

}

int Set::size() const {

	return m_size;

}

bool Set::insert(const ItemType& value) {

	//cout << "1" << endl;
	node* temp = new node;
	temp->next = nullptr;
	temp->prev = nullptr;
	temp->value = value;
	//cout << "1" << endl;
	//check if list is empty
	if (empty()) {
		temp->next = head;
		temp->prev = head;
		//cout << "1" << endl;
		head->next = temp;
		//cout << "1" << endl;
		head->prev = temp;
		m_size++;
		return true;

	}

	node* p = new node;

	//iterate through list to check for duplicates
	for (p = head->next; p != head; p = p->next) {
	
		if (p->value == value) return false;
	
	}

	//tail = head->prev
	
	temp->prev = head->prev; //make new node point back to old tail
	temp->next = head; //make new node point forward to dummy node
	head->prev->next = temp; //make new node the last element
	head->prev = temp; //make new node the new tail
	m_size++;

	return true;

}

bool Set::erase(const ItemType& value) {

	if (m_size == 0) return false;

	node* temp = head->next;

	bool found = false;

	//iterate through loop to find match
	for (int i = 0; i < m_size; i++) {
	
		if (temp->value == value) {
			found = true;
			break;
		}
		temp = temp->next;

	}

	if (found == false) return false;

	temp->prev->next = temp->next; 	//make element before temp point to the element after temp
	temp->next->prev = temp->prev;	//make element after temp point back to the element before temp
	temp->prev = nullptr;
	temp->next = nullptr;

	m_size--;

	return true;

}

bool Set::contains(const ItemType& value) const {

	for (node* p = head->next; p != head; p = p->next)
		if (p->value == value)
			return true;

	return false;

}

bool Set::get(int pos, ItemType& value) const {

	int count = 0;

	for (node* p = head->next; p != head; p = p->next) {
	
		count = 0;

		for (node* c = head->next; c != head; c = c->next) {
		
			if (p->value > c->value) {
			
				count++;
			
			}
		
		}
	
		if (count == pos) {
		
			value = p->value;
			return true;
		
		}

	}

	return false;

}

void Set::swap(Set& other) {

	node* temp = new node;

	int thisOldSize = m_size;
	int otherOldSize = other.m_size;

	bool thisIsLarger = false;
	bool otherIsLarger = false;

	node* thisNode = this->head->next;
	node* otherNode = other.head->next;

	int size = m_size - other.m_size;
	int count = 0;

	if (size > 0) {
		thisIsLarger = true;
		size = m_size;
	}
	else { //algorithm will work even if number of elements is equal
		otherIsLarger = true;
		size = other.m_size;
	}

	//make sure that both sets have elements in them
	if (m_size == 0 && other.m_size == 0) {}
	else if (this->m_size > other.m_size) {
		node* temp = this->head->next;

		for (int i = 0; i < m_size; i++) {

			if (i < other.m_size) {
				
				swapItems(thisNode->value, otherNode->value);
				otherNode = otherNode->next;
				temp = temp->next;

			}
			else {
			
				other.insert(thisNode->value);
			
			}

			thisNode = thisNode->next;

		}

		node* last = temp->prev;
		last->next = head;
		node* nextNode = new node;


		for (int i = otherOldSize; i < m_size; i++) {
		
			if (temp != head) {

				nextNode = temp->next;
				delete temp;
				temp = nextNode;

			}
		
		}

	}
	else if (this->m_size <= other.m_size) {
		node* temp = other.head->next;

		for (int i = 0; i < other.m_size; i++) {

			if (i < m_size) {

				swapItems(thisNode->value, otherNode->value);
				thisNode = thisNode->next;
				temp = temp->next;

			}
			else {

				this->insert(otherNode->value);

			}

			otherNode = otherNode->next;

		}
		//std::cout << temp->value << std::endl;

		node* last = temp->prev;
		last->next = other.head;
		node* nextNode = new node;

		//std::cout << m_size - otherOldSize << std::endl;

		for (int i = thisOldSize; i < other.m_size; i++) {

			//std::cout << i << std::endl;
			if (temp != other.head) {

				nextNode = temp->next;
				delete temp;
				temp = nextNode;

			}

		}

	}

	m_size = otherOldSize;
	other.m_size = thisOldSize;

}

void unite(const Set& s1, const Set& s2, Set& result) {

	ItemType temp;

	//empty the list in result if it is not the same as s1 or s2
	if((&result != &s1) && (&result != &s2))
		emptyList(result);

	for (int i = 0; i < s2.size(); i++) {
	
		s2.get(i, temp);
		result.insert(temp);

	}

	for (int i = 0; i < s1.size(); i++) {
	
		s1.get(i, temp);
		result.insert(temp);
	
	}

}

void subtract(const Set& s1, const Set& s2, Set& result) {

	//make copies of s1 and s2 in case either is equal to result
	Set temp1 = s1;
	Set temp2 = s2;

	//empty the list in result
	emptyList(result);

	int m_size_temp1 = temp1.size();
	int m_size_temp2 = temp2.size();

	ItemType x;

	if (m_size_temp2 > m_size_temp1) {

		for (int i = 0; i < m_size_temp2; i++) {

			temp2.get(i, x);
			if (!temp1.contains(x)) result.insert(x); //insert value into temp1 if it is in s2 but not s1

		}

	}

	else if (m_size_temp1 >= m_size_temp2) {

		for (int i = 0; i < m_size_temp1; i++) {

			temp1.get(i, x);
			if (!temp2.contains(x)) result.insert(x); //insert value into result if it is in s1 but not s2

		}

	}

}

void Set::dump() {

	for (node* p = head->next; p != head; p = p->next) {
	
		std::cerr << p->value << std::endl;
	
	}

}

void swapItems(ItemType& a, ItemType& b) {

	int temp = a;
	a = b;
	b = temp;

}

void emptyList(Set& empty) {

	ItemType temp;
	Set holder; //holds values in linked list of unite

	for (int i = 0; i < empty.size(); i++) {

		empty.get(i, temp);
		holder.insert(temp);

	}

	for (int i = 0; i < holder.size(); i++) {

		holder.get(i, temp);
		//std::cout << "->temp" << std::endl;
		empty.erase(temp);

	}

}

