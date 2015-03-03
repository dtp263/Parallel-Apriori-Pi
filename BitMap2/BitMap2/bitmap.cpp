//#include "bitmap.h"
//#include <iostream>
//#include <cstring>
//#include <vector>
//
//template <size_t N>
//BitMap<N>::BitMap(vector<vector<int>> normalized_data)
//{
//	int i = 0, j = 0;
//	for (i = 0; i < sizeof(normalized_data); i++)
//	{
//		for (j = 0; j < sizeof(normalized_data[i]); j++)
//		{
//			map[i].set(normalized_data[i][j]);
//		}
//	}
//
//}
//
//template <size_t N>
//void BitMap<N>::print_map()
//{
//	int i = 0, j = 0;
//	for (i = 0; i < sizeof(map); i++)
//	{
//		cout << map[i] << endl;
//	}
//
//}
//
//template <size_t N>
//void BitMap<N>::build_map(vector<vector<int>> normal_data)
//{
//	int i = 0, j = 0;
//	for (i = 0; i < sizeof(normal_data); i++)
//	{
//		for (j = 0; j < sizeof(normal_data[i]); j++)
//		{
//			map[i].set(normal_data[i][j]);
//		}
//	}
//}