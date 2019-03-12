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
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
	int m_minLen;
	vector<Genome> m_library;
	Trie<string>* m_trie;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    // This compiles, but may not be correct
	m_minLen = minSearchLength;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	m_library.push_back(genome);

	string temp;
	genome.extract(0, genome.length(), temp);

	int genomeNum = m_library.size() - 1; //index of genome in library

	for (int i = 0; i < temp.size() - m_minLen; i++) {
		string ans = "(Genome " + to_string(genomeNum) + string(", position ") + to_string(i) + ")";
		m_trie->insert(temp.substr(i, i + m_minLen), ans);
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

	if (exactMatchOnly) {
		
		string smallFragment = fragment.substr(0, m_minLen);
		vector<string> temp = m_trie->find(smallFragment, exactMatchOnly);
		
		if (temp.size() == 0) return false;

		for (int i = 0; i < temp.size(); i++) {
			
			string gene = temp[i];
			int num = getGeneNum(gene);
			int index = getGeneIndex(gene);

			string seq;
			m_library[num].extract(index, minimumLength - m_minLen, seq);//get portion that was not checked in trie->find

			bool isMatch = true;
			int c = 0;
			for (int i = m_minLen; i < minimumLength; i++) {
				if (seq[c] != fragment[i]) {
					isMatch = false;
				}
				c++;
			}

			if (isMatch) {//if it is a match, add it to DNAMatch
				DNAMatch tempMatch;
				tempMatch.genomeName = m_library[num].name();
				tempMatch.position = index;
				tempMatch.length = fragment.size();
				matches.push_back(tempMatch);
			}

		}

	}
	
	//TODO: do the same except for exactMatch = false;

    return false;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
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
