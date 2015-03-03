#ifndef BITMAP_H
#define BITMAP_H

#include <cstdio>
#include <vector>
#include <bitset>

using namespace std;

template <size_t N>
class BitMap
{
public:
	vector<bitset<N>> map;

	BitMap() {}
	// Nomalized means that it is now item_numbers rather than what was in the file
	BitMap(vector<vector<int>> normalized_data);

public:
	void print_map();
	void build_map(vector<vector<int>> normal_data);
	void build_map(vector<vector<int> > data, vector<int> unique_identifiers);
};

template <size_t N>
BitMap<N>::BitMap(vector<vector<int>> normalized_data)
{
	this.build_map(normalized_data);
}

template <size_t N>
void BitMap<N>::build_map(vector<vector<int> > data, vector<int> unique_identifiers)
{
	map.resize(data.size());
	int i = 0, j = 0;
	for (i = 0; i < data.size(); i++)
	{
		for (j = 0; j < data[i].size(); j++)
		{
			//vector<int> tmp = find(unique_identifiers.begin(), unique_identifiers.end(), data[i][j]);
			//size_t index = tmp - data[i].begin();
			size_t index = (find(unique_identifiers.begin(), unique_identifiers.end(), data[i][j]) - unique_identifiers.begin());
			map[i].set(index);
		}
	}
}



template <size_t N>
void BitMap<N>::build_map(vector<vector<int>> normalized_data)
{
	map.resize(normal_data.size());
	int i = 0, j = 0;
	for (i = 0; i < normal_data.size(); i++)
	{
		for (j = 0; j < normal_data[i].size(); j++)
		{
			map[i].set(normal_data[i][j]);
		}
	}
}

template <size_t N>
void BitMap<N>::print_map()
{
	int i = 0, j = 0;
	for (i = 0; i < map.size(); i++)
	{
		cout << map[i].to_string() << endl;
	}

}


#endif