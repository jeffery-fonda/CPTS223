#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <unordered_map>

#include "StringSplitter.h"

using namespace std;

int main(int argc, char *argv[])
{
	string key = "";
	string data = "";
	string first_line = "";
	string assignments = "";
	string file_name = "";
	string details = "";
	string totals = "";
	string line_details = "";
	string line_totals = "";
	int sum = 0;

	vector<string> vector_details = StringSplitter::split(line_details, ",");
	vector<string> vector_totals = StringSplitter::split(line_totals, ",");

	string line = "";
	vector<string> new_line = StringSplitter::split(line, ",");

	unordered_map<string, string> table_students{};
	table_students[key] = data;

	unordered_map<string, int> table_sums{};
	table_sums[key] = sum;

	for (int i = 1; i < argc; i++)
	{
		ifstream input_file{ argv[i] }; //open file for reading
		file_name = argv[i];

		if (input_file.is_open() == true) //if the file opens successfully
		{
			//if the file was opened, we can begin reading
			//read first two lines
			getline(input_file, line_details);
			vector<string> vector_details = StringSplitter::split(line_details, ",");
			for (int j = 2; j < vector_details.size(); j++)
			{
				details += vector_details[j];
			}
			getline(input_file, line_totals);
			vector<string> vector_totals = StringSplitter::split(line_totals, ",");
			for (int k = 2; k < vector_totals.size(); k++)
			{
				totals += vector_totals[k];
			}

			while (input_file.good() == true) //going through and reading each line in the file
			{
				getline(input_file, line);
				vector<string> new_line = StringSplitter::split(line, ","); //split lint into vector to get key

				key = new_line[0]; //key is the first section of the vector
				data = new_line[1] + "," + new_line[2]; //this is temporary to get names
				sum = stoi(new_line[3]);
				for (int m = 4; m < new_line.size(); m++) //this loop removes the "totals" from the line
				{
					data += "," + new_line[m];
				}
				
				//looking for an exisiting key
				if (table_students.find(key) == table_students.end())
				{
					table_students.emplace(key, data); //key doesn't exist, insert data into table
				}
				else if (table_students.find(key) != table_students.end())
				{
					vector<string> temp_data = StringSplitter::split(data, ","); //key does exist, edit new data
					for (int n = 2; n < temp_data.size(); n++) //removes key and name from line
					{
						table_students[key] += "," + temp_data[n]; //append the data in the table
					}
				}
				if (table_sums.find(key) == table_sums.end())
				{
					table_sums.emplace(key, sum);
				}
				else if (table_sums.find(key) != table_sums.end())
				{
					table_sums[key] += sum;
				}
			}
		}
		else if (input_file.is_open() == false)
		{
			std::cout << "something done fucked up!" << endl;
		}
		input_file.close();
	}

	ofstream output_file1{ "summary.csv" };
	ofstream output_file2{ "details.csv" };
	for (int i = 1; i < argc; i++)
	{
		cout << argv[i] << endl;
	}
	for (auto item : table_students)
	{
		output_file1 << item.first << ": " << item.second << endl;
		output_file2 << item.first << ": " << item.second << endl;
	}
	for (auto item : table_sums)
	{
		output_file1 << item.first << ": " << item.second << endl;
		output_file2 << item.first << ": " << item.second << endl;
	}

	output_file1.close();
	output_file2.close();
}