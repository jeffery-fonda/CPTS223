#include "ADTs\AvlTree.h"
#include "ADTs\PreOrderTraversal.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//tests left imbalance
void leftTest()
{
	cout << endl << "Testing left imbalance on add of 10-9-8..." << endl;
	AvlTree<int> avl{};
	avl.addElement(10);
	avl.addElement(9);
	avl.addElement(8);

	BinarySearchTree<int> bst{};
	bst.addElement(10);
	bst.addElement(9);
	bst.addElement(8);

	cout << "AVL pre-order traversal: ";
	avl.traverse(PreOrderTraversal<int>{});
	cout << endl << "BST pre-order traversal ";
	bst.traverse(PreOrderTraversal<int>{});
}

//tests right imbalance
void rightTest()
{
	cout << endl << "Testing right imbalance on add of 1-2-3..." << endl;
	AvlTree<int> avl{};
	avl.addElement(1);
	avl.addElement(2);
	avl.addElement(3);

	BinarySearchTree<int> bst{};
	bst.addElement(1);
	bst.addElement(2);
	bst.addElement(3);

	cout << "AVL pre-order traversal: ";
	avl.traverse(PreOrderTraversal<int>{});
	cout << endl << "BST pre-order traversal ";
	bst.traverse(PreOrderTraversal<int>{});
}

int main(int argc, char* argv[])
{
	leftTest();
	cout << endl;
	rightTest();
	cout << endl;
}