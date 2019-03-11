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
void combine(std::vector<ValueType> &copyInto, std::vector<ValueType> copyFrom) {
	for (int i = 0; i < copyFrom.size(); i++) {
		copyInto.push_back(copyFrom[i]);
	}
	/*for (int i = 0; i < copyInto.size(); i++) {
		std::cout << copyInto[i] << std::endl;
	}*/
}

template<typename ValueType>
std::vector<ValueType> recursiveFind(const std::string&	key, bool exactMatchOnly, node<ValueType>* root, int index){
	
	std::vector<ValueType> temp;
	if (root == nullptr) return temp;//if root is nullptr, return empty vector

	char check = key[index];

	if (root->children.size() == 0 && (!exactMatchOnly || root->key == check)) {
		if (index != key.size() - 1) return temp;
		combine(temp, root->value);
		return temp;
	}

	if (root->key != check) {
		if (index == 0 || exactMatchOnly == true) return temp; //if first char of key or if we need to be exact, return empty temp
		exactMatchOnly = true; //otherwise, indicate that we have used up our only mismatch 
	}

	for (int i = 0; i < root->children.size(); i++) {
		combine(temp, recursiveFind(key, exactMatchOnly, root->children[i], index + 1));
	}

	return temp;
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string&	key, bool exactMatchOnly) const {
	std::vector<ValueType> temp;
	for (int i = 0; i < root->children.size(); i++)
		combine(temp, recursiveFind(key, exactMatchOnly, root->children[i], 0));

	return temp;
}

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
