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
		for (int i = _items.size() / 2; i >= 0; i--)
		{
			adjustHeap(i);
		}
	}

	//MA #8 TODO: Implement!
	//Percolates the item specified at by index down into its proper location within a heap.  Used
	//for dequeue operations and array to heap conversions
	void adjustHeap(int index)
	{
		int min = 0;
		int left = 2 * index;
		int right = 0;

		while (right <= _items.getSize())
		{
			left = 2 * index;
			right = 2 * index + 1;
			
			if (_items[right] < _items[index])
			{
				min = right;
				swap(_items[index], _items[min]);
			}
			if (_items[left] > _items[index])
			{
				min = left;
				swap(_items[index], _items[min]);
			}

			index++;

			if (index > _items.getSize() - 1)
			{
				break;
			}
		}
		_items[min] = _items.getElementAt(index);
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