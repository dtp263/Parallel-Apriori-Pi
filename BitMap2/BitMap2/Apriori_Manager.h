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
	void print_unique_identifiers();
	void build_bitmap(string type);
	void write_bitmap_file(string target_file);
	int count_frequency(vector<int> set);
	vector<vector<int>> generate_set(int length);
	vector<int> generate(int offset, int length, vector<int> *items, vector<int> *combo, vector<vector<int>> *set_o_sets);

private:
	
	void define_unique_identifiers(vector<vector<int> > data_matrix);
};

// Apriori_Manager constructor
template <size_t N>
Apriori_Manager<N>::Apriori_Manager(string filename)
{
	m_target_filename = filename;
}


// will build a bitmap using the m_filename
// Arg: type refers to what kind of data the filename holds
// type = "raw"		=> the file contains raw items numbers
//					=> will also build a list of unique_identifiers 
// type = "bit"		=> the file conntains binary strings
template <size_t N>
void Apriori_Manager<N>::build_bitmap(string type)
{
	FileManager fmanager = FileManager(m_target_filename);
	if (type == "raw")
	{
		vector<vector<int> > data_matrix;
		data_matrix = fmanager.get_raw_data();
		define_unique_identifiers(data_matrix);
		m_map.build_map(data_matrix, m_unique_identifiers);
	}
	else if (type == "bit")
	{
		vector<string> data_matrix;
		data_matrix = fmanager.get_bitmap_data();
		m_map.build_map(data_matrix);
	}
}


template <size_t N>
int Apriori_Manager<N>::count_frequency(vector<int> set)
{
	bitset<N> a;
	int i;
	for (i = 0; i < set.size(); i++)
	{
		a.set(set[i]);
	}
	return m_map.count_freq(a.to_string());
}

template <size_t N>
void Apriori_Manager<N>::define_unique_identifiers(vector<vector<int> > data_matrix)
{
	vector<int> flat_data;
	int i, j;
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
vector<int> generate(int offset, int length, vector<int> *items, vector<int> *combo, vector<vector<int>> *set_o_sets)
{
	if (length == 0) {
		/*pretty_print(combination);*/
		set_o_sets->push_back(combo);
		return combo;
	}
	for (int i = offset; i <= items->size() - length; ++i) {
		combo->push_back(items[i]);
		generate(i + 1, length - 1, items, combo, set_o_sets);
		combo->pop_back();
	}
}

template <size_t N>
vector<vector<int>> Apriori_Manager<N>::generate_set(int length)
{
	vector<int> *items = new vector<int>;
	vector<int> *combo = new vector<int>;
	vector<vector<int>> *set_o_sets = new vector<vector<int>>;
	for (int i = 0; i < N; ++i) 
	{ 
		items->push_back(i + 1); 
	}
	generate(0, length, items, combo, set_o_sets);
	const vector<vector<int>> final_set = &set_o_sets;
	return final_set;
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

template <size_t N>
void Apriori_Manager<N>::write_bitmap_file(string target_file)
{
	FileManager f_manager = FileManager(target_file);
	vector<string> string_map;
	int i = 0;
	for (i = 0; i < m_map.map.size(); i++)
	{
		string_map.push_back(m_map.map[i].to_string());
	}
	f_manager.write_bitmap(string_map);
}



#endif