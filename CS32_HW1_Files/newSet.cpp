#include "newSet.h"
#include <iostream>

Set::Set() {

	m_size = 0;
	m_items = new ItemType[DEFAULT_MAX_ITEMS];
	m_max = DEFAULT_MAX_ITEMS;

}

Set::~Set() {

	delete[] m_items;

}

Set::Set(const int maxSize) {

	m_size = 0;
	m_items = new ItemType[maxSize];
	m_max = maxSize;

}

Set::Set(const Set& other) {

	m_size = other.m_size;
	
	m_items = new ItemType[m_size];
	m_items = other.m_items;

	m_max = other.m_max;

}

Set& Set::operator=(const Set& rhs) {

	if (this != &rhs) {
	
		Set temp(rhs);
		swap(temp);
	
	}

	return *this; 

}

int Set::size() const{

	return m_size;

}

bool Set::insert(const ItemType& value) {

	if(contains(value)) return false;

	if (m_size == m_max) return false;

	m_items[m_size] = value;
	m_size++;

	return true;

}

bool Set::contains(const ItemType& value) const {

	for (int i = 0; i < m_size; i++) {

		if (value == m_items[i]) return true;

	}

	return false; 
}

bool Set::erase(const ItemType& value) {

	if (!contains(value)) return false;

	int index;

	for (int i = 0; i < m_size; i++) {

		if (value == m_items[i]) index = i;

	}

	m_size--;
	for (int i = index; i < m_size; i++) {

		m_items[i] = m_items[i + 1];

	}

	return true;
}

bool Set::get(int i, ItemType& value) {

	if (i >= m_size || i < 0) return false;

	int count = 0;

	for (int c = 0; c < m_size; c++) {
	
		count = 0;

		for (int j = 0; j < m_size; j++) {
		
			if (m_items[c] > m_items[j]) {
			
				count++;
			
			}

		}

		if (count == i) {

			value = m_items[c];
			return true;

		}
	
	}

	return false;

}

void Set::swap(Set& other) {

	//swap size
	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;

	//swap max
	temp = m_max;
	m_max = other.m_max;
	other.m_max = temp;

	//swap arrays
	ItemType* tempPtr = m_items;
	m_items = other.m_items;
	other.m_items = tempPtr;
}

bool Set::empty() const{

	return m_size == 0;

}

//void Set::print() const {
//
//	for (int i = 0; i < m_size; i++) std::cout << m_items[i] << std::endl;
//
//	std::cout << "max size: " << m_max << std::endl;
//
//}