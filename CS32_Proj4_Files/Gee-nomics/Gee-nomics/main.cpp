#include <iostream>
#include "Trie.h"

using namespace std;

template<typename ValueType>
void recursivePrint(node<ValueType>* root, int level) {
	if (root == nullptr) return;
	cout << "level " << level << ":";
	for (int i = 0; i < root->children.size(); i++) {
		if(root->children[i] != nullptr)
			cout << root->children[i]->key << " ";
	}
	cout << endl;
	for (int i = 0; i < root->children.size(); i++) {
		recursivePrint(root->children[i], level + 1);
	}
}

template<typename ValueType>
void Trie<ValueType>::print() {
	recursivePrint(root, 1);
}

int main() {
	Trie<int> temp;
	temp.insert("TCGAGCTATTAGGAC", 6);
	temp.insert("TCGAGCTATTAGGAF", 8);
	temp.print();
	return 0;
}