#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>

using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
	string m_name;
	string m_seq;
};



GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    // This compiles, but may not be correct
	m_name = nm;
	m_seq = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
	string line;
	string name;
	string gene = "";
	bool first = true;
	int count = 0;

	while (getline(genomeSource, line)) {
		
		//cout << line << endl;

		if (line[0] == '>') {

			if (first) {
				first = false;
			}

			else if (!first) {
				genomes.push_back(Genome(name, gene));
				gene = "";
			}

			if (line.size() == 1) return false;

			name = line.substr(1);

			//cout << name << endl;

		}

		else {

			char c;

			for (int i = 0; i < line.size(); i++) {
				c = toupper(line[i]);
				if (c != 'A' && c != 'C' && c != 'T' && c != 'G' && c != 'N') return false;
				gene += c;
			}

		}

	}

	//cout << gene << endl;

	genomes.push_back(Genome(name, gene));

	//cout << "hello" << endl;

    return true;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
    return m_seq.size();  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	if (position + length > m_seq.size()) {
		return false;
	}

	fragment = "";

	for (int i = position; i < position + length; i++)
		fragment += m_seq[i];

    return true;  // This compiles, but may not be correct
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
	m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
	delete m_impl;
}

Genome::Genome(const Genome& other)
{
	m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
	GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
	delete m_impl;
	m_impl = newImpl;
	return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
	return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
	return m_impl->length();
}

string Genome::name() const
{
	return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
	return m_impl->extract(position, length, fragment);
}

