#include "ADTs\BinarySearchTree.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void bstTest(BinarySearchTree<int> &bst)
{
	//add some data
	bst.addElement(100);
	bst.addElement(150);
	bst.addElement(125);
	bst.addElement(25);
	bst.addElement(50);
	bst.addElement(10);
	bst.addElement(5);
	bst.addElement(110);

	//check to see if 110 is in the right place
	bool found = false;
	cout << "Searching for value 110: ";
	BinaryNode<int> *root = bst.getRoot();
	if (root != nullptr)
	{
		if (root->getRightChild() != nullptr)
		{
			root = root->getRightChild();
			if (root->getLeftChild() != nullptr)
			{
				root = root->getLeftChild();
				if (root->getLeftChild() != nullptr)
				{
					root = root->getLeftChild();
					if (root->getValue() == 110)
					{
						cout << "Found" << endl;
						found = true;
					}
				}
			}
		}
	}
	if (found == false)
	{
		cout << "Not found" << endl;
	}

	//check to see if 50 is in the right place
	found = false;
	root = bst.getRoot();
	cout << "Searching for value 50: ";
	if (root != nullptr)
	{
		if (root->getLeftChild() != nullptr)
		{
			root = root->getLeftChild();
			if (root->getRightChild() != nullptr)
			{
				root = root->getRightChild();
				if (root->getValue() == 50)
				{
					cout << "Found" << endl;
					found = true;
				}
			}
		}
	}
	if (found == false)
	{
		cout << "Not found" << endl;
	}

	//remove 25, check for rebalance
	found = false;
	root = bst.getRoot();
	bst.removeElement(25);
	cout << "Removing value 25, new value: ";
	if (root != nullptr)
	{
		if (root->getLeftChild() != nullptr)
		{
			root = root->getLeftChild();
			cout << root->getValue() << endl;
			found = true;
		}
	}
	if (found == false)
	{
		cout << "Unknown" << endl;
	}
	found = false;

	//remove 100, check for rebalance
	found = false;
	root = bst.getRoot();
	bst.removeElement(100);
	cout << "Removing value 100, new value: ";
	if (root != nullptr)
	{
		cout << root->getValue() << endl;
		found = true;
	}
	if (found == false)
	{
		cout << "Unknown" << endl;
	}


}

int main(int argc, char *argv[])
{
	BinarySearchTree<int> bst{};
	bstTest(bst);
}