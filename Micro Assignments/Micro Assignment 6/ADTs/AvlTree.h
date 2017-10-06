#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BinarySearchTree.h"
#include "AvlNode.h"

template <typename T>
class AvlTree : public BinarySearchTree<T>
{
protected:

	//MA #6 TODO: IMPLEMENT ME THIRD!
	//The purpose of this function is to figure out where the imbalance occurs within root (left or right)
	//and return the result of the appropriate rotation (left or right) on root's child.
	virtual BinaryNode<T> * balance(AvlNode<T> *root)
	{
		//check for null roots
		if (root == nullptr)
		{
			return root;
		}

		//get left and right children, convert into AVL Nodes
		AvlNode<T> *left = dynamic_cast<AvlNode<T> *>(root->getLeftChild());
		AvlNode<T> *right = dynamic_cast<AvlNode<T> *>(root->getRightChild());

		//MA #6 TODO: remove return and fully implement!
		//Once you find the imbalance, you will need to either return the result of rotateLeft or rotateRight
		return root;
	}

	//MA #6 TODO: IMPLEMENT ME SECOND!
	virtual BinaryNode<T> *rotateLeft(BinaryNode<T> *root)
	{
		//check for null roots
		if (root == nullptr)
		{
			return root;
		}

		//new root comes from right side
		AvlNode<T> *new_root = dynamic_cast<AvlNode<T> *>(root->getRightChild());

		//1. At the node whose left and right height differ by more than one, do the following
		//2. Let CurrentRoot = the node identified in step #1
		//3. Let NewRoot = CurrentRoot's rightchild
		//4. Set CurrentRoot's rightchild = NewRoot's leftchild
		//5. Set NewRoot's leftchild = CurrentRoot

		//MA #6 TODO: rotate left and return "new_root"
		return setHeight(new_root);
	}

	//MA #6 TODO: IMPLEMENT ME FIRST!
	virtual BinaryNode<T> *rotateRight(BinaryNode<T> *root)
	{
		//check for null roots
		if (root == nullptr)
		{
			return root;
		}

		//new root comes from left side
		AvlNode<T> *new_root = dynamic_cast<AvlNode<T> *>(root->getLeftChild());

		//1. At the node whose left and right height differ by more than one, do the following
		//2. Let CurrentRoot = the node identified in step #1
		//3. Let NewRoot = CurrentRoot's leftchild
		//4. Set CurrentRoot's leftchild = NewRoot's rightchild
		//5. Set NewRoot's rightchild = CurrentRoot

		//MA #6 TODO: rotate right and return "new_root"
		return setHeight(new_root);
	}

	virtual BinaryNode<T> * setHeight(AvlNode<T> * root)
	{
		//check for null roots
		if (root == nullptr)
		{
			return root;
		}

		//get left and right children, convert into AVL Nodes
		AvlNode<T> *left = dynamic_cast<AvlNode<T> *>(root->getLeftChild());
		AvlNode<T> *right = dynamic_cast<AvlNode<T> *>(root->getRightChild());

		//start at height 1 because I'm representing nullptrs with values of -1
		int height = 1;

		//add in largest of left or right heights
		int left_height = left == nullptr ? -1 : left->getHeight();
		int right_height = right == nullptr ? -1 : right->getHeight();
		height += (left_height < right_height) ? right_height : left_height;

		//reassign new height to root
		root->setHeight(height);

		//check to see if balance factor is out of whack
		int balance_factor = root->getBalanceFactor();
		if (balance_factor < -1 || balance_factor > 1)
		{
			return balance(root);
		}
		return root;
	}

	virtual BinaryNode<T> * addElementHelper(BinaryNode<T> *root, const T& item)
	{
		//BASE CASE: create new node
		if (root == nullptr)
		{
			root = new AvlNode<T>{};
			root->setValue(item);
			return root;
		}

		//else, just call BST helper
		BinaryNode<T> *bst_result = BinarySearchTree::addElementHelper(root, item);

		//if everything went according to plan, we should be able to cast the BinaryNode
		//into an AvlNode
		AvlNode<T> *avl_node = dynamic_cast<AvlNode<T>*>(bst_result);

		//return balanced node
		setHeight(avl_node);
	}

	virtual BinaryNode<T> *removeElementHelper(BinaryNode<T> *root, const T& item)
	{
		//call parent's method
		BinaryNode<T> *bst_result = BinarySearchTree::removeElementHelper(root, item);

		//if everything went according to plan, we should be able to cast the BinaryNode
		//into an AvlNode
		AvlNode<T> *avl_node = dynamic_cast<AvlNode<T>*>(bst_result);

		//if we don't have a nullptr, balance node
		if (avl_node != nullptr)
		{
			return setHeight(avl_node);
		}
	}
};
#endif