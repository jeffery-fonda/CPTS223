#ifndef HEAP_H
#define HEAP_H

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <ostream>
#include <cstdlib>
#include <istream>
#include <fstream>
#include <unordered_map>

#include "ADTs\Vector.h"
#include "ADTs\Queue.h"
#include "StringSplitter.h"

using namespace std;

struct Job //created a struct to hold all the information for a "Job"
{
	string name; //the name (J1, J2 etc.)
	int CPUs; //how many CPUs that job requires
	int duration; //how long it will take that job to execute
	int time_started; //a variable to keep track of what tick that job was started at
	int time_ended; //a variable to keep track of when the job finished

	bool const operator < (const Job &rhs) //had to overload some comparison operators in order to use Adam's heap code
	{
		if (rhs.duration < duration)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool const operator > (const Job &rhs)
	{
		if (rhs.duration > duration)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool const operator == (const Job &rhs)
	{
		if (duration == rhs.duration)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

//everything below here is all Adam's code from the micro assignments
template<typename T>
class Heap : Queue<T>
{
private:
	Vector<T> _items;

	void buildHeap()
	{
		for (int i = _items.size() / 2; i >= 0; i--)
		{
			adjustHeap(i);
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

	//Adds a new item to the heap
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

	//Returns the top-most item in our heap without actually removing the item from the heap
	virtual T& getFirst()
	{
		return _items[0];
	}

	//Removes the top-most item from the heap and returns it to the caller
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