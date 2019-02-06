#include "SSNSet.h"
#include <iostream>

SSNSet::SSNSet() {}

bool SSNSet::add(ItemType ssn) {

	return m_set.insert(ssn);

}

int SSNSet::size() const {

	return m_set.size();

}

void SSNSet::print() const {

	ItemType temp;

	for (int i = 0; i < m_set.size(); i++) {
	
		m_set.get(i, temp);

		std::cout << temp << std::endl;
	
	}

}

