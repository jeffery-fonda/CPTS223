#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "BinaryFile.h"
#include "StringSplitter.h"
#include "PA2.h"


using namespace std;

//reads a file in from binary information
static vector<string> readFile(string input_file_name)
{
	vector<string> result{};
	ifstream input_file{ input_file_name, ios::binary };
	if (input_file.is_open() == true)
	{
		string line = "";
		while (input_file.good() == true)
		{
			getline(input_file, line);
			result.push_back(line);
		}
	}
	return result;
}

//test function for PA2
void pa2Test()
{
	vector<string> files{ "test.txt", "savio.txt", "kennedy.txt" };
	for (string file : files)
	{
		cout << "Analzying file " << file << "..." << endl;

		//PROVIDED: read contents of file into vector of strings
		vector<string> file_contents = readFile(file);

		//PA #2: build tree
		HuffmanTree<char> *coding_tree = PA2::huffmanTreeFromText(file_contents);

		//PA #2: generate encoding map
		unordered_map<char, string> encoder = PA2::huffmanEncodingMapFromTree(coding_tree);

		//PROVIDED: convert file into vector of bits
		vector<bool> raw_stream = PA2::toBinary(file_contents, encoder);

		//PROVIDED: write vector of bits to separate file
		vector<string> pieces = StringSplitter::split(string(file), ".");
		string file_name = pieces[0];
		string extension = "";
		if (pieces.size() > 1)
		{
			extension = pieces[1];
		}

		string output_file_name = string(file_name) + ".pa2c";
		BinaryFile::writeToFile(raw_stream, output_file_name);

		//PA #2: write map to file
		string map_file = string(file_name) + ".pa2m";
		PA2::writeEncodingMapToFile(encoder, map_file);

		//PA #2: get bits back from file
		vector<bool> bits_from_file = BinaryFile::readFromFile(output_file_name);

		//PA #2: read map from file
		unordered_map<char, string> encoder_from_file = PA2::readEncodingMapFromFile(map_file);

		//PA #2: convert file bits back into text
		string text = PA2::decodeBits(bits_from_file, encoder_from_file);

		//PA #2: write decompressed back to file
		output_file_name = string(file_name) + "_1." + extension;
		ofstream output_file{ output_file_name };
		output_file << text;
		output_file.close();

		delete coding_tree;
	}
}

//outputs PA2 exe usage
void outputUsage()
{
	cout << "Usage: <exe name> <Action> <File1> <File2>" << endl;
	cout << "Actions (must be lower case):" << endl;
	cout << "test - runs buit-in unit test functions" << endl;
	cout << "compress - compresses <File1>" << endl;
	cout << "decompress - decompresses <File1> into <File2>" << endl;
}


int main(int argc, char* argv[])
{
	//calling for unit tests?
	if (argc == 2)
	{
		if (string(argv[1]) == "test")
		{
			pa2Test();
			return 0;
		}
		outputUsage();
		return 0;
	}
	else if(argc == 3)
	{
		if (string(argv[1]) == "compress")
		{
			string to_compress = string(argv[2]);
			cout << "Compressing file " << to_compress << "..." << endl;
			vector<string> file_contents = readFile(to_compress);

			//PA #2: build tree
			HuffmanTree<char> *coding_tree = PA2::huffmanTreeFromText(file_contents);

			//PA #2: generate encoding map
			unordered_map<char, string> encoder = PA2::huffmanEncodingMapFromTree(coding_tree);

			//PROVIDED: convert file into vector of bits
			vector<bool> raw_stream = PA2::toBinary(file_contents, encoder);

			//PROVIDED: write vector of bits to separate file
			vector<string> pieces = StringSplitter::split(string(to_compress), ".");
			string file_name = pieces[0];
			string extension = "";
			if (pieces.size() > 1)
			{
				extension = pieces[1];
			}
			string output_file_name = string(file_name) + ".pa2c";
			BinaryFile::writeToFile(raw_stream, output_file_name);

			//PA #2: write map to file
			string map_file = string(file_name) + ".pa2m";
			PA2::writeEncodingMapToFile(encoder, map_file);

			delete coding_tree;
		}
		else
		{
			outputUsage();
			return 0;
		}
	}
	else if (argc == 4)
	{
		if (string(argv[1]) == "decompress")
		{
			cout << "Decompressing " << argv[2] << "..." << endl;

			string to_decompress = argv[2];
			string extract_location = argv[3];

			//separate extension from name in to_decompress
			vector<string> pieces = StringSplitter::split(string(to_decompress), ".");
			string file_name = pieces[0];
			string extension = "";
			if (pieces.size() > 1)
			{
				extension = pieces[1];
			}

			//PA #2: get bits back from file
			vector<bool> bits_from_file = BinaryFile::readFromFile(to_decompress);

			//PA #2: read map from file
			unordered_map<char, string> encoder_from_file = PA2::readEncodingMapFromFile(file_name + ".pa2m");

			//PA #2: convert file bits back into text
			string text = PA2::decodeBits(bits_from_file, encoder_from_file);

			//PA #2: write decompressed back to file
			ofstream output_file{ extract_location };
			output_file << text;
			output_file.close();
		}
		else
		{
			outputUsage();
			return 0;
		}
	}
	else
	{
		outputUsage();
		return 0;
	}
}