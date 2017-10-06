#include <string>
#include <iostream>
#include <cstdlib>
#include "ADTs\HashTables\LinearHashTable.h"
#include "ADTs\HashTables\SimpleStringHasher.h"
using namespace std;

//make sure that HT is empty before running!
void hashTableTest(HashTableBase<string, string> &ht)
{
	ht.addElement("I", "Love");
	ht.addElement("CptS", "223");
	ht.addElement("And", "I");
	ht.addElement("especially", "love");
	ht.addElement("Hashtables", "!");

	//test inputs
	vector<HashItem<string, string>> &items = ht.getItems();
	
	if (items[0].getKey() != "especially")
	{
		cout << "Key failure: especially";
		cout << endl;
	}
	else
	{
		cout << "Key success: especially";
		cout << endl;
	}

	if (items[8].getKey() != "I")
	{
		cout << "Key failure: I";
		cout << endl;
	}
	else
	{
		cout << "Key success: I";
		cout << endl;
	}

	if (items[10].getValue() != "223")
	{
		cout << "Value failure: 223";
		cout << endl;
	}
	else
	{
		cout << "Value success: 223";
		cout << endl;
	}

	if (items[1].getKey() != "Hashtables")
	{
		cout << "Key failure: Hashtables";
		cout << endl;
	}
	else
	{
		cout << "Key success: Hashtables";
		cout << endl;
	}

	//remove test
	ht.removeElement("especially");
	ht.removeElement("And");
	items = ht.getItems();
	if (items[0].isEmpty() == true && items[0].getKey() == "especially")
	{
		cout << "Remove key \"especially\" success.";
		cout << endl;
	}
	else
	{
		cout << "Remove key \"especially\" failure.";
		cout << endl;
	}
	if (items[2].isEmpty() == true && items[2].getKey() == "And")
	{
		cout << "Remove key \"And\" success.";
		cout << endl;
	}
	else
	{
		cout << "Remove key \"And\" failure.";
		cout << endl;
	}

}

int main(int argc, char *argv[])
{
	LinearHashTable<string, string> ht{ new SimpleStringHasher{} };
	hashTableTest(ht);
}