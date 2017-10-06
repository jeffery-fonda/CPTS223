#ifndef HEAP_H
#define HEAP_H

#include "Vector.h"
#include "Queue.h"
using namespace std;

template<typename T>
class Heap : Queue<T>
{
private:
	Vector<T> _items;

	void buildHeap()
	{
		for (int i = _items.getSize() / 2; i >= 0; i--)
		{
			adjustHeap(i);
		}
	}

	//MA #8 TODO: Implement!
	//Percolates the item specified at by index down into its proper location within a heap.  Used
	//for dequeue operations and array to heap conversions
	void adjustHeap(int index)
	{
		//presumably, the item at location index is not where it should be.
		//Store it in a temp variable for now
		T item = _items[index];

		//we need to percolate down to the bottom of our heap
		int current_size = _items.getSize();

		//loop until we've gone past the size of our vector
		while (index < current_size)
		{
			//calculate the left child of the where 
			int child_position = index * 2 + 1;

			//are we at the end of our vector?
			if (child_position < current_size)
			{
				//check to make sure we're in bounds before performing the check below
				if (child_position + 1 < current_size)
				{
					//is the right child smaller than the left child?
					if (_items[child_position + 1] < _items[child_position])
					{
						//if so, follow the right child's branch
						child_position++;
					}
				}

				//is the item smaller than the smallest of our two children?
				if (item < _items[child_position])
				{
					//if so, then we found our match and we're good to go!
					_items[index] = item;
					break;
				}
				else
				{
					//The item is not smaller than its children.  Swap the smallest
					//child with its smallest child, and update index to account for
					//the more likely position
					T *val = &_items[child_position];
					_items[index] = *val;
					index = child_position;
				}
			}
			else
			{
				//Where ever index ended up is where our original item belongs.  Set now.
				_items[index] = item;
				break;
			}
		}
	}

public:
	Heap()
	{
	}

	Heap(const Vector<T> &unsorted)
	{
		for (int i = 0; i < unsorted.getSize(); i++)
		{
			_items.push(unsorted.getElementAt(i));
		}
		buildHeap();
	}
	virtual void enqueue(T item)
	{
		//calculate positions
		int current_position = _items.getSize();
		int parent_position = (current_position - 1) / 2;

		//insert element (note: may get erased if we hit the WHILE loop)
		_items.addElement(item);

		//get parent element if it exists
		T *parent = nullptr;
		if (parent_position >= 0)
		{
			parent = &_items[parent_position];
		}

		//only continue if we have a non-null parent
		if (parent != nullptr)
		{
			//bubble up
			while (current_position > 0 && item < *parent)
			{
				_items[current_position] = *parent;
				current_position = parent_position;
				parent_position = (current_position - 1) / 2;
				if (parent_position >= 0)
				{
					parent = &_items[parent_position];
				}
			}

			//after finding the correct location, we can finally place our item
			_items[current_position] = item;
		}
	}

	virtual T& getFirst()
	{
		return _items[0];
	}

	virtual T dequeue()
	{
		int last_position = _items.getSize() - 1;
		T last_item = _items[last_position];
		T top = _items[0];
		_items[0] = last_item;
		_items.removeElementAt(last_position);

		//percolate down
		adjustHeap(0);
		return top;
	}

#pragma region Collection overrides
	bool isEmpty() const
	{
		return _items.getSize() == 0;
	}

	virtual void addElement(T item)
	{
		return enqueue(item);
	}
	virtual int getSize() const
	{
		return _items.getSize();
	}

#pragma endregion

};

#endif