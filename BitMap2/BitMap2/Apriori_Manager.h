#ifndef APRIORI_MANAGER_H
#define APRIORI_MANAGER_H
#include <iostream>
#include "FileManager.h"
#include "bitmap.h"
#include <vector>
#include <set>

using namespace std;

template <size_t N>
class Apriori_Manager
{
public:
	string m_target_filename;
	float m_minimum_support;
	vector<int> m_unique_identifiers;
	BitMap<N> m_map;

	Apriori_Manager() { }
	Apriori_Manager(string filename);

public:
	void define_unique_identifiers();
	void build_bitmap();

	void print_unique_identifiers();

};

// Apriori_Manager constructor
template <size_t N>
Apriori_Manager<N>::Apriori_Manager(string filename)
{
	m_target_filename = filename;
}

template <size_t N>
void Apriori_Manager<N>::build_bitmap()
{
	vector<vector<int> > data_matrix;
	FileManager fmanager = FileManager(m_target_filename);
	data_matrix = fmanager.get_raw_data();
	m_map.build_map(data_matrix, m_unique_identifiers);
}

template <size_t N>
void Apriori_Manager<N>::define_unique_identifiers()
{
	vector<int> flat_data;
	int i, j;
	vector<vector<int> > data_matrix;
	FileManager fmanager = FileManager(m_target_filename);
	data_matrix = fmanager.get_raw_data();
	
	for (i = 0; i < data_matrix.size(); i++) 
	{
		for (j = 0; j < data_matrix[i].size(); j++)
		{
			cout << data_matrix[i][j] << " ";
			flat_data.push_back(data_matrix[i][j]);
		}
		cout << endl;
	}
	

	// Used sets because this flat data will be massive.
	// There might be a better way to do this...
	set<int> s;
	unsigned size = flat_data.size();
	for (unsigned i = 0; i < size; ++i)
	{
		s.insert(flat_data[i]);
	}
	flat_data.assign(s.begin(), s.end());
	m_unique_identifiers = flat_data;
}

template <size_t N>
void Apriori_Manager<N>::print_unique_identifiers()
{
	int i;
	for (i = 0; i < m_unique_identifiers.size(); i++)
	{
		cout << i << " :: " << m_unique_identifiers[i] << endl;
	}
}


#endif