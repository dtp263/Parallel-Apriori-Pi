#include "bitmap.h"
#include "Apriori_Manager.h"
#include <vector>
#include <iostream>
#include <algorithm>

#include <iostream>
#include <string>
#include <cstring>


using namespace std;

int main()
{
	// declare num of different items
	const size_t num_of_items = 5;



	string filename = "test2.txt";
	string slave_file = "slave_file.txt";
	cout << "Test of: " << filename << endl;

	Apriori_Manager<num_of_items> a_manager(filename);

	cout << endl << "Dataset" << endl;
	a_manager.build_bitmap("raw");
	


	cout << endl << "Item ID Number :: Item Value" << endl;
	a_manager.print_unique_identifiers();

	
	cout << endl << "==========Managers Map==========" << endl;
	a_manager.m_map.print_map();

	a_manager.write_bitmap_file(slave_file);


	cout << endl << "::::::Read from bit file and build bitmap test:::::" << endl;




	Apriori_Manager<num_of_items> b_manager(slave_file);
	b_manager.build_bitmap("bit");
	b_manager.m_map.print_map();


	cout << endl << "==========================Frequency counting tests==========================" << endl;
	vector<int> tmp_vec;
	
	int j, tmp;
	for (j = 0; j < num_of_items; j++)
	{
		tmp_vec.push_back(j);
		tmp = b_manager.count_frequency(tmp_vec);
		cout << "Item " << j << ": " << tmp << endl;
		tmp_vec.clear();
	}

	// TODO: issue with returning the "set_o_sets" variable
	// 
	//vector<vector<int>> sets = b_manager.generate_set(1);

	cin.ignore();

}