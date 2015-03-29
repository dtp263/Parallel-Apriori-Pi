#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "itemset.h"
#include "bitmap.h"

#include <time.h>


using namespace std;

class FileManager
{
public:
	string m_filename;

	FileManager() {}
	FileManager(string filename);

public:
	vector<vector<int>> get_raw_data();
	vector<vector<bool>> get_bitmap_data(unsigned int width);

	void write_frequency_count(int* count);
	void write_bitmap(vector<vector<bool>> map);
	void write_results(vector<ItemSet> sets);
};

// FileManager constructor
FileManager::FileManager(string filename)
{
	m_filename = filename;
}

// Get raw data from the filename
vector<vector<int> > FileManager::get_raw_data()
{
	printf("START get_raw_data\n");
	ifstream file(m_filename);
	bool int_end = false;
	int item = 0, i;
	vector<vector<int>> result;
	vector<int> line_entry, trans_entry;
	char buffer[2048];
	clock_t clock_2_start = clock();
	do
	{
		file.read(&buffer[0u], sizeof(buffer));
		int k = file.gcount();
		for (i = 0; i < k; ++i)
		{
			switch (buffer[i])
			{
			case '\r': case '\n': case ' ':
				int_end = true;
				break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':
				item = 10 * item + buffer[i] - '0';
				break;
			default:
				cerr << "Bad format\n";
			}
			if (int_end)
			{
				line_entry.push_back(item);
				if (line_entry.size() == 2)
				{
					if (result.size() == line_entry.front())
					{
						result.back().push_back(line_entry.back());
					}
					else
					{
						result.push_back(vector<int>(1, line_entry.back()));
					}
					line_entry.clear();
				}
				item = 0;
				int_end = false;
			}
		}
	} while (file);

	clock_t clock_2_end = clock();
	printf("[2] Time: %f\n", (double)(clock_2_end - clock_2_start) / (double)CLOCKS_PER_SEC);
	file.close();
	return result;
}

vector<vector<bool>> FileManager::get_bitmap_data(unsigned int width)
{
	string line;
	vector<vector<bool>> result;
	vector<bool> tmp(width, 0);
	FILE *file;
	//// open binary file for 
	file = fopen(m_filename.c_str(), "rb");
	if (file)
	{
		fread(&tmp, sizeof(tmp), 1, file);
	}
	else { cout << "Bitmap file not open..." << endl; }

	return result;
}

void FileManager::write_bitmap(vector<vector<bool>> map)
{
	//ofstream file;
	////file.open(m_filename, ios::binary | ios::out, ios::trunc);
	unsigned int width = map[0].size();
	FILE *file;
	//// open binary file for 
	file = fopen(m_filename.c_str(), "wb");
	if (!file)
	{
		cout << "Error bitmap file to write isnt open..." << endl;
		return;
	}
	int i = 0;
	for (i = 0; i < map.size(); i++)
	{
		fwrite(&(map[i]), sizeof(map[i]), 1, file);
		//file.write(&(map[i]), width);
	}
	fclose(file);
}

void FileManager::write_results(vector<ItemSet> sets)
{
	ofstream outfile;
	outfile.open(m_filename, ios_base::app);
	vector<ItemSet>::iterator it = sets.begin();
	for (;  it < sets.end(); ++it)
	{
		outfile << (*it).to_pretty_string() << endl;
	}
}



#endif