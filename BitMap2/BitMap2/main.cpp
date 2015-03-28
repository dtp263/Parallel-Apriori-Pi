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

// need to pass in args
// args[0] = target_filename
// args[1] = 

int main()
{
	// declare constants for now
	// these will be arguements for main later on
	const int generator_input = 100;
	
	const double min_support = .5;

	// test file naminmg uses this syntax:
	//		{num_of_items * 1000}x{num_of_transactions * 1000}
	//		ex.	100x1000.txt  ==>  100,000 different items & 1 million transactions

	
	// HARDER TESTS
	//string filename = "1x1.txt";
	string filename = "100x1000.txt";
	const size_t num_of_items = generator_input * 1000;
	// END TEST

	// SIMPLE TEST
	//string filename = "test2.txt";
	//const size_t num_of_items = 5;
	// END TEST

	// needs to be set for intitial tests to be correct
	unsigned int num_of_transactions = 1000000;
	string limit_test;
	int free_space;

	cout << "Number of different items : " << num_of_items << endl;
	
	cout << "Number of transactions: ~ 1 million" << endl;

	string slave_file = "slave_file.txt";
	cout << "Test of: " << filename << endl;

	vector<bitset<num_of_items>> max_test1;
	printf("Vector<bitset<%d>> MAX_SIZE is: %d\n", num_of_items, max_test1.max_size());
	limit_test = (max_test1.max_size() > num_of_transactions) ? "pass" : "fail";
	free_space = max_test1.max_size() - num_of_transactions;
	printf("\t%d < %d = %s (%d)\n\n", max_test1.max_size(), num_of_transactions, limit_test.c_str(), free_space);

	list<bitset<num_of_items>> max_test2;
	printf("List<bitset<%d>> MAX_SIZE is: %d\n", num_of_items, max_test2.max_size());
	limit_test = (max_test2.max_size() > num_of_transactions) ? "pass" : "fail";
	free_space = max_test2.max_size() - num_of_transactions;
	printf("\t%d < %d = %s (%d)\n\n", max_test2.max_size(), num_of_transactions, limit_test.c_str(), free_space);


	cout << "Array<bitset<" << num_of_items << ">> MAX_SIZE is: " << SIZE_MAX << endl;
	limit_test = (SIZE_MAX > num_of_transactions) ? "pass" : "fail";
	free_space = int(SIZE_MAX - (size_t)num_of_transactions);
	cout << "\t" << SIZE_MAX << " < " << num_of_transactions << " = " << limit_test << endl;
	cout << (int)free_space << endl << endl;


	set<bitset<num_of_items>> max_test3;
	printf("Set<bitset<%d>> MAX_SIZE is: %d\n", num_of_items, max_test3.max_size());
	limit_test = (max_test3.max_size() > num_of_transactions) ? "pass" : "fail";
	free_space = max_test3.max_size() - num_of_transactions;
	printf("\t%d < %d = %s(%d)\n\n", max_test3.max_size(), num_of_transactions, limit_test.c_str(), free_space);



	vector<vector<bool>> max_test4;
	printf("Vector<vector<bool>> MAX_SIZE is: %d\n", num_of_items, max_test4.max_size());
	limit_test = (max_test4.max_size() > num_of_transactions) ? "pass" : "fail";
	printf("\t%d < %d = %s(%d)\n\n", max_test4.max_size(), num_of_transactions, limit_test.c_str(), max_test4.max_size() - num_of_transactions);


	//printf("\t max_size / num_of_different_items = max_capacity_for_transactions\n");


	/*int max_capacity_for_transactions = max_test4.max_size() / num_of_items;
	printf("\t %d / %d = %d\n", max_test4.max_size(), num_of_items, max_capacity_for_transactions);
	limit_test = (max_capacity_for_transactions > num_of_transactions) ? "pass" : "fail";
	free_space = max_capacity_for_transactions - num_of_transactions;
	printf("\t\t%d < %d = %s(%d)\n\n", max_capacity_for_transactions, num_of_transactions, limit_test.c_str(), free_space);
*/


	Apriori_Manager<num_of_items> a_manager(filename);

	cout << endl << "Dataset" << endl;
	a_manager.build_bitmap("raw");
	


	cout << endl << "Item ID Number :: Item Value" << endl;
	//a_manager.print_unique_identifiers();

	
	cout << endl << "==========Managers Map==========" << endl;
	//a_manager.m_map.print_map();

	a_manager.write_bitmap_file();


	cout << endl << "::::::Read from bit file and build bitmap test:::::" << endl;



	// Create another instance of Apriori_Manager to test:
	//		+ read text file containing bitmap
	//		+ build bitmap with that file
	Apriori_Manager<num_of_items> b_manager(filename);
	b_manager.build_bitmap("bit");
	//b_manager.m_map.print_map();
	int map_size = a_manager.m_map.map.size();
	int freq_for_minsup = (int)(a_manager.m_map.map.size() * (double)min_support);


	cout << endl << "==========================Initial Count==========================" << endl;
	// create itemset manager and store the initial count in it

	ItemSet_Manager set_manager(a_manager.initial_count());

	set_manager.prune_sets(map_size, min_support);
	//cout << set_manager.to_pretty_string() << endl;
	a_manager.write_results_file_initial(set_manager.sets);

	cout << endl << "==========================New Sets==========================" << endl;
	
	int cc = 2;
	while (set_manager.sets.size() > 1)
	{
		printf("\nCount %d\n", cc);
		set_manager.generate_sets();
		set_manager.sets = a_manager.count_multiple_frequencies(set_manager.sets);
		set_manager.prune_sets(map_size, min_support);
		//cout << set_manager.to_pretty_string() << endl;
		a_manager.write_results_file(set_manager.sets);
		cc++;
	}
	
	cout << endl << "END PROCESS";

	cin.ignore();

}