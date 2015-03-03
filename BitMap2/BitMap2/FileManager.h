#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class FileManager
{
public:
	string m_filename;

	FileManager() {}
	FileManager(string filename);

public:
	vector<vector<int>> get_raw_data();
	int* get_bitmap_data();

	void write_frequency_count(int* count);
	void write_bitmap(int* int_map);
};

// FileManager constructor
FileManager::FileManager(string filename)
{
	m_filename = filename;
}

// Get raw data from the filename
vector<vector<int> > FileManager::get_raw_data()
{
	string line;
	int tmp1 = 1, tmp2 = 0;
	string buf;
	vector<int> tmp_line;
	vector< vector<int> > data_matrix;
	ifstream file(m_filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			
			stringstream ss(line);
			ss >> buf;
			tmp2 = atoi(buf.c_str());
			ss >> buf;
			if (tmp2 != tmp1)
			{
				data_matrix.push_back(tmp_line);
				tmp_line.clear();
				tmp1 = tmp2;
			}
			tmp_line.push_back(atoi(buf.c_str()));
		}
	}
	else
	{
		cout << "Error: file did not open...\n";
	}
	return data_matrix;
}


#endif