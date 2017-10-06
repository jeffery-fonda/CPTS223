#include "ADTs\BinarySearchTree.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void getHeightTest()
{
	BinarySearchTree<int> bst{};
	bst.addElement(1);
	bst.addElement(2);
	bst.addElement(5);
	bst.addElement(4);
	bst.addElement(6);
	cout << "Height: " << bst.getHeightRec() << endl;
}

void isFullTest()
{
	BinarySearchTree<int> bst{};
	bst.addElement(1);
	bst.addElement(2);
	bst.addElement(5);
	bst.addElement(4);
	bst.addElement(6);
	cout << "Is full test #1: " << bst.isFull() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(5);
	bst.addElement(15);
	bst.addElement(2);
	bst.addElement(6);
	cout << "Is full test #2: " << bst.isFull() << endl;


	//PERSONAL TEST CASE, NOT ADAM'S
	//bst = BinarySearchTree<int>{};
	//bst.addElement(1);
	//bst.addElement(2);
	//bst.addElement(5);
	//bst.addElement(4);
	//bst.addElement(6);
	//cout << "Is full test #2: " << bst.isFull() << endl;
}

void isCompleteTest()
{
	BinarySearchTree<int> bst{};
	bst.addElement(1);
	bst.addElement(2);
	bst.addElement(3);
	cout << "Is complete test #1: " << bst.isComplete() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(2);
	bst.addElement(3);
	bst.addElement(1);
	cout << "Is complete test #2: " << bst.isComplete() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(2);
	bst.addElement(3);
	bst.addElement(1);
	bst.addElement(25);
	bst.addElement(30);
	cout << "Is complete test #3: " << bst.isComplete() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(2);
	bst.addElement(3);
	bst.addElement(1);
	bst.addElement(25);
	bst.addElement(30);
	bst.addElement(22);
	cout << "Is complete test #3: " << bst.isComplete() << endl;
}

void isAvlCompliantTest()
{
	BinarySearchTree<int> bst{};
	bst.addElement(1);
	bst.addElement(2);
	bst.addElement(3);
	cout << "Is AVL complaint test #1: " << bst.isAvlCompliant() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(9);
	bst.addElement(8);
	cout << "Is AVL complaint test #2: " << bst.isAvlCompliant() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(5);
	bst.addElement(15);
	cout << "Is AVL complaint test #3: " << bst.isAvlCompliant() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(5);
	bst.addElement(1);
	bst.addElement(3);
	bst.addElement(15);
	cout << "Is AVL complaint test #4: " << bst.isAvlCompliant() << endl;

	bst = BinarySearchTree<int>{};
	bst.addElement(10);
	bst.addElement(5);
	bst.addElement(1);
	bst.addElement(8);
	bst.addElement(15);
	bst.addElement(11);
	bst.addElement(20);
	bst.addElement(25);
	cout << "Is AVL complaint test #4: " << bst.isAvlCompliant() << endl;
}

int main(int argc, char* argv[])
{
	getHeightTest();
	isFullTest();
	isCompleteTest();
	isAvlCompliantTest();
	
}