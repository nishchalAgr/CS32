#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
struct node {
	node() {};
	std::vector<ValueType> value;
	char key;
	std::vector<node*> children;
};

template<typename ValueType>
class Trie
{
public:
	Trie() {
		root = new node<ValueType>;
		root->key = '1';
	}
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
	void print();
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
	node<ValueType>* root;
};

template<typename ValueType>
void deleteTree(node<ValueType>* root) {
	if (root == nullptr) return;
	for (int i = 0; i < root->children.size(); i++)
		deleteTree(root->children[i]);
	delete root;
}

template<typename ValueType>
void Trie<ValueType>::reset() {
	deleteTree(root);
	root = new node;
}

template<typename ValueType> 
Trie<ValueType>::~Trie() {
	deleteTree(root);
}

template<typename ValueType>
void recursiveInsert(const std::string& key, const ValueType& value, node<ValueType>* root) {
	if (root == nullptr || key == "") return; //base case

	std::string restOfKey;
	char check = key[0]; //get first letter of key

	if (root->key == '1') {//check if we are root node, it cannot contain a DNA base, so we are basically skipping it
		//std::cout << "TRUE" << std::endl;
		restOfKey = key;
	}
	else {
		if (key.size() > 1) restOfKey = key.substr(1); //get rest of key
		else restOfKey = "";

		if (root->key == '-') { //if node's key is empty(which means we just added it), make its key equal to check
			root->key = check;
		}

		if (restOfKey == "") {//if restOfKey is empty add value
			root->value.push_back(value);
			return;
		}

		check = restOfKey[0]; //make check the next char in key because that is what is relevent to the child nodes
	}

	for (int i = 0; i < root->children.size(); i++) {
		if (root->children[i] != nullptr && root->children[i]->key == check) {
			std::cout << "TRUE " << check <<  std::endl;
			recursiveInsert(restOfKey, value, root->children[i]);
			return;
		}
	}

	node<ValueType>* temp = new node<ValueType>;
	temp->key = '-';
	root->children.push_back(temp);
	recursiveInsert(restOfKey, value, temp);

}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value) {
	recursiveInsert(key, value, root);
}

#endif // TRIE_INCLUDED
