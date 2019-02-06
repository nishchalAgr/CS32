#include "Set.h"

Set::Set() {

	m_size = 0;

}

int Set::size() const{

	return m_size;

}

bool Set::insert(const ItemType& value) {

	if(contains(value)) return false;

	if (m_size == DEFAULT_MAX_ITEMS) return false;

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

	if (!contains(value) || m_size <= 0) return false;

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

bool Set::get(int i, ItemType& value) const{

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

	int size = m_size;
	ItemType temp;


	if (other.m_size > m_size) {
	
		size = other.m_size;
	
	}

	//swap each element in the array
	for (int i = 0; i < size; i++) {
	
		temp = m_items[i];
		m_items[i] = other.m_items[i];
		other.m_items[i] = temp;
	
	}

	//swap the lengths
	size = m_size;
	m_size = other.m_size;
	other.m_size = size;

}

bool Set::empty() const{

	return m_size == 0;

}