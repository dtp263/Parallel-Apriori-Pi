#ifndef ITEMSET_H
#define ITEMSET_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>
#include <string>

using namespace std;

class ItemSet
{
public:
	vector<int> set;
	int count = 0;

public:
	ItemSet() { }
	ItemSet(std::vector<int> t_set);

	string to_set_string();
	string to_pretty_string();
	void clear();
};


ItemSet::ItemSet(vector<int> t_set)
{
	set = t_set;
}

string ItemSet::to_set_string()
{
	string output = "";
	int i;
	for (i = 0; i < set.size(); i++)
	{
		output += to_string(set[i]) + " ";
	}
	return output.substr(0, output.size() - 1);
}

string ItemSet::to_pretty_string()
{
	string output = "Items: ";
	output += to_set_string() + " || Count = " + to_string(count);
	return output;
}

void ItemSet::clear()
{
	set = vector<int>();
	count = 0;
}


#endif;