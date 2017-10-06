#include "PA2.h"

//PA #2 TODO: finds the smallest tree in a given forest, allowing for a single skip
int PA2::findSmallestTree(vector<HuffmanTree<char> *> forest, int index_to_ignore)
{
	//Finds the smallest tree (by weight) in the supplied forest.  
	//Note that this function accepts a second optional parameter of an index to skip.  
	//Use this index to allow your function to also find the 2nd smallest tree in the 
	//forest.

	HuffmanTree<char> *smallest_tree;
	HuffmanTree<char> *second_smallest;

	smallest_tree = forest[0];
	second_smallest = forest[0];
	int smallest_tree_index = 0;

	for (int i = 0; i < forest.size(); i++)
	{
		if (forest[i]->getWeight() < smallest_tree->getWeight())
		{
			smallest_tree = forest[i];
			smallest_tree_index = forest[i]->getWeight();
		}
	}

	for (int j = 0; j < forest.size(); j++)
	{
		if (forest[j]->getWeight() < second_smallest->getWeight() && j != index_to_ignore)
		{
			second_smallest = forest[j];
		}
	}

	return smallest_tree_index; //might need to change to index_to_ignore
}

//PA #2 TOOD: Generates a Huffman character tree from the supplied text
HuffmanTree<char>* PA2::huffmanTreeFromText(vector<string> data)
{
	//Builds a Huffman Tree from the supplied vector of strings.
	//This function implement's Huffman's Algorithm as specified in page 
	//456 of the book.

	//step 1: build frequency distribution of all characters
	//use this frequency distribution to build your forest

	//vector<HuffmanTree<char>*> forest{};
	//HuffmanTree<char> *merged_tree = new HuffmanTree<char>(smallest, second_smallest);

	//In order for your tree to be the same as mine, you must take care 
	//to do the following:
	//1.	When merging the two smallest subtrees, make sure to place the 
	//      smallest tree on the left side!
	//2.	Have the newly created tree take the spot of the smallest 
	//		tree in the forest(e.g.vector[smallest] = merged_tree).
	//3.	Use vector.erase(begin() + second_smallest_index) to remove 
	//      the other tree from the forest.

	vector<HuffmanTree<char>*> forest{};
	vector<int> frequency;

	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].length(); j++)
		{
			data[i][j] = toupper(data[i][j]);
			++(frequency[data[i][j] - 'A']);
		}
	}

	int i = 0;

	vector<HuffmanLeafNode<char>*> vector_of_leaves{};

	while (frequency.size() != 0)
	{
		HuffmanLeafNode<char> *leaf = new HuffmanLeafNode<char>((i + 'A'), frequency[i]);
		vector_of_leaves.push_back(leaf);
		i++;
	}

	int smallest_weight = vector_of_leaves[0]->getWeight();
	int second_smallest_weight = vector_of_leaves[0]->getWeight();
	int location_smallest = 0;
	int location_second_smallest = 0;

	while (vector_of_leaves.size() != 0)
	{
		for (int k = 0; k < vector_of_leaves.size(); k++)
		{
			if (vector_of_leaves[k]->getWeight() < smallest_weight)
			{
				smallest_weight = vector_of_leaves[k]->getWeight();
				location_smallest = k;
			}
		}

		vector_of_leaves.erase(vector_of_leaves.begin() + location_smallest);

		for (int m = 0; m < vector_of_leaves.size(); m++)
		{
			if (vector_of_leaves[m]->getWeight() < second_smallest_weight && m != smallest_weight)
			{
				second_smallest_weight = vector_of_leaves[m]->getWeight();
				location_second_smallest = m;
			}
		}

		vector_of_leaves.erase(vector_of_leaves.begin() + location_second_smallest);

		HuffmanTree<char> *merged_tree = new HuffmanTree<char>(smallest_weight, second_smallest_weight);
		forest[location_smallest] = merged_tree;
		forest.erase(forest.begin() + location_second_smallest);
		location_smallest = 0;
		location_second_smallest = 0;
	}

	return forest[location_smallest];
}

//PA #2 TODO: Generates a Huffman encoding map from the supplied Huffman tree
//NOTE: I used a recursive helper function to solve this!
unordered_map<char, string> PA2::huffmanEncodingMapFromTree(HuffmanTree<char> *tree)
{
	//Generates a Huffman Map based on the supplied Huffman Tree.  Again, recall 
	//that a Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.  
	//As such, a given code represents a pre-order traversal of that bit of the 
	//tree.  I used recursion to solve this problem.
	unordered_map<char, string> result{};



	return result;
}

//PA #2 TODO: Generates a Huffman character tree from the supplied encoding map
//NOTE: I used a recursive helper function to solve this!
HuffmanTree<char>* PA2::huffmanTreeFromMap(unordered_map<char, string> huffmanMap)
{
	//Generates a Huffman Tree based on the supplied Huffman Map.Recall that a 
	//Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.
	return nullptr;
}

//PA #2 TODO: Writes an encoding map to file.  Needed for decompression.
void PA2::writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name)
{
	//Writes the supplied encoding map to a file.  My map file has one 
	//association per line (e.g. 'a' and 001).  Each association is separated by 
	//a sentinel value.  In my case, I went with a double pipe (||).
}

//PA #2 TODO: Reads an encoding map from a file.  Needed for decompression.
unordered_map<char, string> PA2::readEncodingMapFromFile(string file_name)
{
	//Creates a Huffman Map from the supplied file.Essentially, this is the 
	//inverse of writeEncodingMapToFile.  Be sure to use my StringSplitter class 
	//to make your life easier!
	unordered_map<char, string> result{};
	return result;
}

//PA #2 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
string PA2::decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap)
{
	//Uses the supplied Huffman Map to convert the vector of bools (bits) back into text.
	//To solve this problem, I converted the Huffman Map into a Huffman Tree and used 
	//tree traversals to convert the bits back into text.
	ostringstream result{};
	return result.str();
}

//PA #2 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
vector<bool> PA2::toBinary(vector<string> text, unordered_map<char, string> huffmanMap)
{
	vector<bool> result{};
	return result;
}