#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
	~GenomeMatcherImpl();
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
	int m_minLen;
	vector<Genome> m_library;
	Trie<string>* m_trie;
};

GenomeMatcherImpl::~GenomeMatcherImpl() {
	delete m_trie;
}

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    // This compiles, but may not be correct
	m_minLen = minSearchLength;
	m_trie = new Trie<string>;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	m_library.push_back(genome);
	
	string temp;
	genome.extract(0, genome.length(), temp);
	
	int genomeNum = m_library.size() - 1; //index of genome in library
	
	for (int i = 0; i < temp.size() - m_minLen; i++) {

		string ans = "(Genome " + to_string(genomeNum) + string(", position ") + to_string(i) + ")";
		//cout << temp.substr(i, m_minLen) << endl;
		m_trie->insert(temp.substr(i, m_minLen), ans);
	
	}
    // This compiles, but may not be correct
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minLen;  // This compiles, but may not be correct
}

int getGeneNum(string gene) {
	
	bool isNum = false;
	string index = "";
	
	for (int i = 0; i < gene.size(); i++) {

		if (gene[i] == ',') isNum = false;
		if (isNum) index += gene[i];
		if (gene[i] == ' ') isNum = true;

	}

	stringstream convertToInt(index);
	
	int ans = -1;
	convertToInt >> ans;
	
	return ans;

}

int getGeneIndex(string gene) {

	int spaces = 0;
	bool isNum = false;
	string index = "";

	for (int i = 0; i < gene.size(); i++) {

		if (gene[i] == ')') isNum = false;
		if (isNum) index += gene[i];
		if (gene[i] == ' ') {
			spaces++;
			if (spaces == 3) isNum = true;
		}

	}

	stringstream convertToInt(index);

	int ans = -1;
	convertToInt >> ans;

	return ans;

}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (minimumLength < m_minLen || fragment.size() < minimumLength) return false;

	string smallFragment = fragment.substr(0, m_minLen);
	vector<string> temp = m_trie->find(smallFragment, exactMatchOnly);;

	//if (temp.empty()) cout << "EMPTY" << endl;

	//cout << minimumLength << endl;
	//cout << fragment.size() << endl;

	if (temp.size() == 0) return false;

	if (true) {
		
		for (int i = 0; i < temp.size(); i++) {

			string gene = temp[i];
			int num = getGeneNum(gene); //which genome is this from
			//cout << i << " num   :" << num << endl;
			int index = getGeneIndex(gene); //which index in the genome
			//cout << i << " index :" << index << endl;

			int isNotMatch = 0;
			int size = minimumLength;
			bool match = true;

			for (int c = minimumLength; c <= fragment.size(); c++) {//check each size above the minimum
				
				isNotMatch = 0;

				string seq;
				m_library[num].extract(index, c, seq);//get entire portion, we need to check for one mismatch
				
				cout << "seq: " << seq << " - fragment: " << fragment << endl;

				for (int a = 0; a < c; a++) {
					if (fragment[a] != seq[a]) {
						isNotMatch++;
						//cout << "match: " << isNotMatch << endl;
						if (exactMatchOnly) { 
							match = false;
							break;
						}
						if (!exactMatchOnly && (a == 0 || isNotMatch == 2)) {
							match = false;
							break; //if more than one mismatch, dont add it and go to the next genome
						}
					}

				}

				if (exactMatchOnly && isNotMatch == 0) size = c; //no mismatch allowed for exact match 
				if (!exactMatchOnly && isNotMatch < 2) size = c;//one mismatch allowed for exactMatchOnly = false
			}

			if (match) {

				DNAMatch tempMatch;
				tempMatch.genomeName = m_library[num].name();
				tempMatch.position = index;
				tempMatch.length = size; //add the matching genome with the largest size
				matches.push_back(tempMatch);

			}

		}

		return !(matches.size() == 0); //if no matches were found return false, return true otherwise

	}

	////below if exactMatchOnly is true
	//for (int i = 0; i < temp.size(); i++) {
	//		
	//	string gene = temp[i];
	//	int num = getGeneNum(gene);
	//	int index = getGeneIndex(gene);

	//	string seq;
	//	m_library[num].extract(index + m_minLen, minimumLength - m_minLen, seq);//get portion that was not checked in trie->find

	//	bool isMatch = true;
	//	int c = 0;
	//	for (int j = index + m_minLen; j < index + minimumLength - m_minLen; j++) {
	//		if (seq[c] != fragment[j]) {
	//			isMatch = false;
	//		}
	//		c++;
	//	}

	//	if (isMatch) {//if it is a match, add it to DNAMatch
	//		DNAMatch tempMatch;
	//		tempMatch.genomeName = m_library[num].name();
	//		tempMatch.position = index;
	//		tempMatch.length = fragment.size();
	//		matches.push_back(tempMatch);
	//	}

	//}

	//return !(matches.size() == 0); 
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	int numOfFragments = query.length() / fragmentMatchLength;

	//cout << "-----" << endl;
	//cout << fragmentMatchLength << endl;
	//cout << numOfFragments << endl;

	int count = 0;
	vector<DNAMatch> temp;

	for (int i = 0; i < numOfFragments; i++) {

		string seq;
		query.extract(i*fragmentMatchLength, fragmentMatchLength, seq);
		//cout << seq << endl;
		findGenomesWithThisDNA(seq, fragmentMatchLength, exactMatchOnly, temp);

	}

	/*for (int i = 0; i < temp.size(); i++) {
		cout << temp[i].genomeName << " " << temp[i].position << " " << temp[i].length << endl;
	}

	cout << "-----" << endl;
*/
	list<GenomeMatch> ans;

	for (int i = 0; i < m_library.size(); i++) {
		
		count = 0;

		for (int j = 0; j < temp.size(); j++) {
			
			if (temp[j].genomeName == m_library[i].name()) count++;

		}

		double percent = double(count) / double(numOfFragments) * 100;

		//cout << "count: " << count << endl;
		//cout << "percent: " << percent << endl;

		if (percent >= matchPercentThreshold) {
		
			GenomeMatch tempMatch;
			tempMatch.genomeName = m_library[i].name();
			tempMatch.percentMatch = percent;
		
			if (ans.empty()) ans.push_back(tempMatch);

			else {
			
				for (list<GenomeMatch>::iterator p = ans.begin(); p != ans.end(); p++) { //this is for inserting the genomeMatch in the correct order
				
					if (percent > (*p).percentMatch) {
						ans.insert(p, tempMatch);
						break;
					}

					else if (percent == (*p).percentMatch) {
					
						if (tempMatch.genomeName > (*p).genomeName)//if alphabetically greater, iterate forward and add the 
							p++;

						if (p == ans.end()) {
							ans.push_back(tempMatch);
							break;
						}

						ans.insert(p, tempMatch);		
						break;
					}
				
				}
			
			}

		}

	}

	for (list<GenomeMatch>::iterator p = ans.begin(); p != ans.end(); p++) { //push sorted elements in list to results
		results.push_back(*p);
	}
	//if (double(count) / double(numOfFragments) >= matchPercentThreshold) return true;
    return true;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
