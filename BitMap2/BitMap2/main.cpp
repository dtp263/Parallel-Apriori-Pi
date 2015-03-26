#include "bitmap.h"
#include "Apriori_Manager.h"
#include "itemset_manager.h"
#include <vector>
#include <iostream>
#include <algorithm>

#include <iostream>
#include <string>
#include <cstring>


using namespace std;

int main()
{
	// declare constants for now
	// these will be arguements for main later on
	const size_t num_of_items = 5;
	const double min_support = .01;


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



	// Create another instance of Apriori_Manager to test:
	//		+ read text file containing bitmap
	//		+ build bitmap with that file
	Apriori_Manager<num_of_items> b_manager(slave_file);
	b_manager.build_bitmap("bit");
	b_manager.m_map.print_map();


	cout << endl << "==========================Initial Count==========================" << endl;
	// create itemset manager and store the initial count in it

	ItemSet_Manager set_manager(a_manager.initial_count());

	cout << set_manager.to_pretty_string() << endl;
	
	cout << endl << "==========================New Sets==========================" << endl;
	
	int freq_for_minsup = (int)(a_manager.m_map.map.size() * (double)min_support);

	set_manager.generate_sets(freq_for_minsup);

	cout << set_manager.to_pretty_string() << endl;

	cout << endl << "==========================Second Count==========================" << endl;

	set_manager.sets = a_manager.count_multiple_frequencies(set_manager.sets);

	cout << set_manager.to_pretty_string() << endl;

	cin.ignore();

}