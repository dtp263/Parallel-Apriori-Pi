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
	void build_map(vector<string> normal_data);
	void build_map(vector<vector<int> > data, vector<int> unique_identifiers);

	int count_freq(string string_set);
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
void BitMap<N>::build_map(vector<string> normalized_data)
{
	int i = 0;
	for (i = 0; i < normalized_data.size(); i++)
	{
		bitset<N> a(normalized_data[i]);
		map.push_back(a);
	}
}

template <size_t N>
int BitMap<N>::count_freq(string string_set)
{
	int count = 0, i;
	bitset<N> set(string_set);
	for (i = 0; i < map.size(); i++)
	{
		bool check = false;
		if ((map[i] & set) == set)
		{
			count++;
			check = true;
		}
		//cout << map[i].to_string() << " :: "
		//	 << set.to_string() << "  ==>  ";
		//cout << (map[i] & set) << "  ->  " << check << endl;
	}
	//cout << endl;
	return count;
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