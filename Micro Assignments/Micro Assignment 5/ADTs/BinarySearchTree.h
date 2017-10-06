#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Collection.h"
#include "BinaryNode.h"
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
		//Assumption: non-null tree
		if (root == nullptr)
		{
			return root;
		}

		//Base case: root is the largest
		//know this brecaise root has no right children
		if (root->getRightChild() == nullptr)
		{
			//Grab root's left child so that we can return it to the caller of this function
			//In the end, whether or not left is null doesn't really matter
			BinaryNode<T> *left = root->getLeftChild();
			delete root;

			//return left pointer to caller
			return left;
		}
		else
		{
			//Recursive case: root isn't the largest
			//In this case, we need to call ourselves again, this time passing ing a value
			//guaranteed to be at least as large as we are
			BinaryNode<T> *new_right = removeLargest(root->getRightChild());

			//reconfigure our right pointer to the returned value
			root->setRightChild(new_right);

			return root;
		}
	}

	//removes the smallest element in the subtree starting at
	//*root
	BinaryNode<T> * removeSmallest(BinaryNode<T> *root)
	{
		//Assumption: non-null tree
		if (root == nullptr)
		{
			return root;
		}

		//Base case: root is the smallest
		//know this brecaise root has no left children
		if (root->getLeftChild() == nullptr)
		{
			//Grab root's right child so that we can return it to the caller of this function
			//In the end, whether or not right is null doesn't really matter
			BinaryNode<T> *right = root->getRightChild();
			delete root;

			//return left pointer to caller
			return right;
		}
		else
		{
			//Recursive case: root isn't the smallest
			//In this case, we need to call ourselves again, this time passing in a value
			//guaranteed to be at least as small as we are
			BinaryNode<T> *new_left = removeSmallest(root->getLeftChild());

			//reconfigure our left pointer to the returned value
			root->setLeftChild(new_left);

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
		//MA #5 TODO: IMPLEMENT!
		//Base case: null root
		if (root == nullptr)
		{
			//Allocate space, store value and then return
			root = new BinaryNode<T>{};
			root->setValue(item);
			return root;
		}

		//Recursive case: root is not null
		if (item >= root->getValue())
		{
			//Case 1: belongs on the right side of root
			BinaryNode<T> *right = addElementHelper(root->getRightChild(), item);

			//update right side with reconfigured state
			root->setRightChild(right);
		}
		else
		{
			//Case 2: belongs on left side of root
			BinaryNode<T> *left = addElementHelper(root->getLeftChild(), item);

			//update left child with reconfigured state
			root->setLeftChild(left);
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