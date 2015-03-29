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
	vector<vector<bool>> map;
	BitMap() {}
	// Nomalized means that it is now item_numbers rather than what was in the file
	BitMap(vector<vector<int>> normalized_data);

public:
	void print_map();
	void build_map(vector<vector<bool>> bit_data);
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
	// Limit on the size of a vector<bitset<N>>
	//		When N is really large the vector wont initialize due to the MAX_SIZE of vector
	map.resize(data.size());
	unsigned int i = 0, j = 0;
	printf("Building Bitmap\n");
	for (i = 0; i < data.size(); i++)
	{
		map[i] = vector<bool>(N, 0);
		for (j = 0; j < data[i].size(); j++)
		{
			size_t index = (find(unique_identifiers.begin(), unique_identifiers.end(), data[i][j]) - unique_identifiers.begin());
			map[i][index] = 1;
		}
	}
}



template <size_t N>
void BitMap<N>::build_map(vector<vector<bool>> bit_data)
{
	/*int i = 0;
	for (i = 0; i < bit_data.size(); i++)
	{
		bitset<N> a(bit_data[i]);
		map.push_back(a);
	}*/
	map = bit_data;
}

template <size_t N>
int BitMap<N>::count_freq(vector<bool> t_set)
{
	unsigned int count = 0, i;
	bitset<N> test_set(t_set);
	bitset<N> transaction();
	for (i = 0; i < map.size(); i++)
	{
		bool check = false;
		transaction(map[i]);
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