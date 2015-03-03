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
	cout << "Test of: " << filename << endl;

	Apriori_Manager<num_of_items> a_manager(filename);

	cout << endl << "Dataset" << endl;
	// raw dataset is printed while defiing uniques
	a_manager.define_unique_identifiers();

	


	cout << endl << "Item ID Number :: Item Value" << endl;
	a_manager.print_unique_identifiers();

	a_manager.build_bitmap();
	cout << endl << "==========Managers Map==========" << endl;
	a_manager.m_map.print_map();

	cin.ignore();

}
