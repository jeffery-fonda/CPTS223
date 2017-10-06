#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Collection.h"
#include "BinaryNode.h"
#include "BinaryTreeTraversal.h"
#include "Vector.h"

template <typename T>
class BinarySearchTree : public Collection<T>
{
private:

	//keeps track of the remove direction (left or right)
	unsigned int _remove_counter = 0;

	//keeps track of BST size
	unsigned int _size_counter = 0;

#pragma region protected methods

protected:
	BinaryNode<T> *_root = nullptr;

	//remotes the largest element from the subtree starting at
	//*root
	BinaryNode<T> * removeLargest(BinaryNode<T> *root)
	{
		//ASSUMPTION: non-null root
		if (root == nullptr)
		{
			return root;
		}

		//BASE CASE: root is largest (has no right node)
		if (root->getRightChild() == nullptr)
		{
			BinaryNode<T> *left = root->getLeftChild();
			delete root;

			//return left information to parent
			return left;
		}
		else
		{
			//RECURSIVE CASE:
			BinaryNode<T> *new_right = removeLargest(root->getRightChild());
			root->setRightChild(new_right);
			return root;
		}
	}

	//removes the smallest element in the subtree starting at
	//*root
	BinaryNode<T> * removeSmallest(BinaryNode<T> *root)
	{
		//ASSUMPTION: non-null root
		if (root == nullptr)
		{
			return root;
		}

		//BASE CASE: root is smallest (has no left node)
		if (root->getLeftChild() == nullptr)
		{
			BinaryNode<T> *right = root->getRightChild();
			delete root;

			//return right information to parent
			return right;
		}
		else
		{
			//RECURSIVE CASE:
			BinaryNode<T> *new_right = removeSmallest(root->getLeftChild());
			root->setLeftChild(new_right);
			return root;
		}
	}

	BinaryNode<T> * findSmallestIter(BinaryNode<T> *root)
	{
		while (root != nullptr && root->getLeftChild() != nullptr)
		{
			root = root->getLeftChild();
		}
		return root;
	}

	BinaryNode<T> * findLargestIter(BinaryNode<T> *root)
	{
		while (root != nullptr && root->getRightChild() != nullptr)
		{
			root = root->getRightChild();
		}
		return root;
	}

	//AC Note: pass by const reference is generally
	//faster than pass by value for larger items
	virtual BinaryNode<T> * addElementHelper(BinaryNode<T> *root, const T& item)
	{
		//BASE CASE: create new node
		if (root == nullptr)
		{
			root = new BinaryNode<T>{};
			root->setValue(item);
			return root;
		}

		//RECURSIVE CASE: figure out which child to call
		//is "item" larger than us?
		if (item >= root->getValue())
		{
			//AC: super tricky way to do this
			//root->setRightChild(addElementHelper(root->getRightChild(), item));

			//AC: more explicit way to do the code above
			BinaryNode<T> *right_child = root->getRightChild();
			BinaryNode<T> *result = addElementHelper(right_child, item);
			root->setRightChild(result);
		}
		else
		{
			//AC note: this code is the same as when we add to the right,
			//except we replace "right" with "left"
			BinaryNode<T> *left_child = root->getLeftChild();
			BinaryNode<T> *result = addElementHelper(left_child, item);
			root->setLeftChild(result);
		}
		return root;
	}

	virtual BinaryNode<T> *removeElementHelper(BinaryNode<T> *root,
		const T& item)
	{
		//ASSUMPTION: root is not null
		if (root == nullptr)
		{
			return root;
		}

		//three possibilities:
		// we found the item (root value == item)
		// item is less than root (item < root)
		// item is greater than root (item > root)
		if (item == root->getValue())
		{
			//increment removal counter
			_remove_counter++;

			//we found the item
			//do we remove from the left or right?
			if (_remove_counter % 2 == 0)
			{
				//check to see if left is not nullptr
				if (root->getLeftChild() != nullptr)
				{
					//left subtree remove
					//we need the largest from the left side
					BinaryNode<T> *largest = findLargestIter(root->getLeftChild());

					//take the largest's value, put inside root
					root->setValue(largest->getValue());

					//having gotten the value, we can now remove the node
					//from the tree
					BinaryNode<T> * result = removeLargest(root->getLeftChild());
					root->setLeftChild(result);
					return root;
				}
				else
				{
					//else, delete us, return the result
					return removeSmallest(root);
				}
			}
			else
			{
				//right subtree remove
				if (root->getRightChild() != nullptr)
				{
					//find the smallest value on the right
					BinaryNode<T> *smallest = findSmallestIter(root->getRightChild());

					//take the smallest value, put into root
					root->setValue(smallest->getValue());

					//now, it's safe to remove the smallest value
					BinaryNode<T> * result = removeSmallest(root->getRightChild());
					root->setRightChild(result);
					return root;
				}
				else
				{
					return removeLargest(root);
				}
			}
		}
		else if (item < root->getValue())
		{
			//item is less than root
			BinaryNode<T> *result = removeElementHelper(
				root->getLeftChild(), //send along our left child
				item				  //and the same item
				);

			//the recursive call *might* have altered our
			//left child's structure.  Inform root of this
			//change
			root->setLeftChild(result);
		}
		else
		{
			//item is greater than root
			BinaryNode<T> *result = removeElementHelper(
				root->getRightChild(),
				item
				);
			root->setRightChild(result);
		}

		//if we didn't return any sooner, return the root now
		return root;
	}
#pragma endregion

public:

	//AC Note: iterative approach to node deletion
	virtual ~BinarySearchTree()
	{
		Vector<BinaryNode<T> *> nodes{};
		nodes.push(_root);
		while (nodes.getSize() > 0)
		{
			BinaryNode<T> *last = nodes.pop();

			//make sure that we're dealing with an actual
			//binary node
			if (last != nullptr)
			{
				//add last's children to the stack
				nodes.push(last->getLeftChild());
				nodes.push(last->getRightChild());

				//having gotten all of the information out of
				//last, we can now delete the node
				delete last;
			}
		}
	}

	void removeElement(T item)
	{
		_root = removeElementHelper(_root, item);
		_size_counter--;
	}

	virtual void addElement(T item)
	{
		_root = addElementHelper(_root, item);
		_size_counter++;
	}

	void traverse(BinaryTreeTraversal<T> &traversal)
	{
		traversal.traverse(_root);
	}

	virtual bool isEmpty() const
	{
		return _root == nullptr;
	}
	virtual int getSize() const
	{
		return _size_counter;
	}

	//for MA #5 unit testing.  Will be removed after.
	BinaryNode<T> *getRoot()
	{
		return _root;
	}
};

#endif