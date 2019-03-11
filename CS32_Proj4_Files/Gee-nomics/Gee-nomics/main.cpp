#include <iostream>
#include <fstream>
#include "provided.h"
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

void somefunc()
{
	//	Specify	the	full	path	and	name	of	the	gene	data	file	on	your	hard	drive.
	string filename = "C:/Users/Nishchal's PC/Documents/CS32/CS32_Proj4_Files/Gee-nomics/data/Desulfurococcus_mucosus.txt";
	//	Open	the	data	file	and	get	a	ifstream object	that	can	be	used	to	read	its
	//	contents.
	ifstream strm(filename);
	if (!strm)
	{
		cout << "Cannot	open " << filename << endl;
		return;
	}
	vector<Genome>	vg;
	bool success = Genome::load(strm, vg);		//	Load	the	data	via	the	stream.
	cout << success << endl;
	if (success)
	{
		cout << "Loaded	" << vg.size() << " genomes successfully:" << endl;
		for (int k = 0; k != vg.size(); k++)
			cout << vg[k].name() << endl;
	}
	else
		cout << "Error loading genome data" << endl;
}		//	destructor	for	ifstream	closes	the	file	

int main() {
	//Trie<int> temp;
	//temp.insert("TCGAGCTATTAGGAC", 6);
	//temp.insert("TCGAGCTATTAGGAL", 8);
	////temp.print();
	//vector<int> vec = temp.find("TCGAGCTATAAGGAC", false);
	//for (int i = 0; i < vec.size(); i++) {
	//	cout << vec[i] << endl;
	//}
	somefunc();
	return 0;
}