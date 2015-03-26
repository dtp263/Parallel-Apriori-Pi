#ifndef ITEMSET_MANAGER_H
#define ITEMSET_MANAGER_H

#include <cstdio>
#include <iostream>
#include <set>
#include "itemset.h"
#include <time.h>
#include <list>

using namespace std;

class ItemSet_Manager
{
public:
	vector<ItemSet> sets;

public:
	ItemSet_Manager() {}
	ItemSet_Manager(vector<ItemSet> t_sets) { sets = t_sets; }

	string to_pretty_string();
	vector<ItemSet> generate_sets(int min_sup_freq);
};

string ItemSet_Manager::to_pretty_string()
{
	int i;
	string output = "Pretty Set Manager Print\n";
	for (i = 0; i < sets.size(); i++)
	{
		output += sets[i].to_pretty_string() + "\n";
	}
	return output;
}

//check the n-1 items, used in join two candidate frequent itemset
//level: the current level of the inputted Itemset
bool compare_chunks(const ItemSet &ck, const ItemSet &ck_1, int level){
	//do not check the last one
	vector<int> ck_item = ck.set;
	vector<int> ck_1_item = ck_1.set;

	int and_cnt = 0;
	int tmp;
	for (and_cnt = 0; and_cnt < level - 1; and_cnt++){

		if (ck_item[and_cnt] != ck_1_item[and_cnt]){
			return false;
		}
	}
	return true;
}

vector<ItemSet> ItemSet_Manager::generate_sets(int min_sup_freq)
{
	vector<ItemSet> tmp;
	clock_t gencandidate_str = clock();

	//current level cnt = the length of current candidate items
	int curlevel = sets[0].set.size();
	int cur_arr_index = curlevel - 1;

	int nextlevel = curlevel + 1;
	int next_arr_index = nextlevel - 1;

	vector<ItemSet> *Ln = &sets;
	// if the new length is 1 then return the original vector
	if (Ln->size() <2){
		return sets;
	}
	vector<ItemSet>*Lnp1 = new vector<ItemSet>();
	vector<ItemSet>::const_iterator c_outter_iter = Ln->begin();
	vector<ItemSet>::const_iterator c_inner_iter;

	for (; c_outter_iter != Ln->end(); ++c_outter_iter){
		c_inner_iter = c_outter_iter;
		c_inner_iter++;
		for (; c_inner_iter != Ln->end(); ++c_inner_iter){
			//check the Ln_1 is equal or not
			if (compare_chunks((*c_inner_iter), (*c_outter_iter), curlevel)){
				//the previous items are equal, then generate a new lnp1
				ItemSet lnp1_item;
				lnp1_item.set.resize(nextlevel);

				//sort with insc by check the last item
				if (c_inner_iter->set[cur_arr_index] > c_outter_iter->set[cur_arr_index]){
					//push the outter first and push the inner
					lnp1_item.set = (*c_outter_iter).set;
					lnp1_item.set.insert(lnp1_item.set.begin() + next_arr_index, c_inner_iter->set[cur_arr_index]);
				}
				else{
					//push the inner first and push the outter
					lnp1_item.set = (*c_outter_iter).set;
					lnp1_item.set.insert(lnp1_item.set.begin() + next_arr_index, c_outter_iter->set[cur_arr_index]);


				}
				// Check if frequent enough

				// TODO: clean this up. I dont think i need to prune just yet.....

				//lnp1_item.bitmap = bitmap_intersect(c_inner_iter->bitmap, c_outter_iter->bitmap, bitmap_length);
				//if (lnp1_item.count < min_sup_freq){
				//	//in-frequent
				//	/*Itemset_free(lnp1_item);*/
				//	lnp1_item.clear();
				//}
				//else
					Lnp1->push_back(lnp1_item);
			}
		}
	}


	//push Lnp1 into Ln_itemsets
	sets = *Lnp1;
	/*sets.push_back(Lnp1);*/

	clock_t gencandidate_end = clock();
	fprintf(stderr, "generate candidate cost:%f\n", (double)(gencandidate_end - gencandidate_str) / (double)CLOCKS_PER_SEC);


	return tmp;
}


#endif