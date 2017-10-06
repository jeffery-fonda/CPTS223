#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>
#include <initializer_list>
#include "Indexed.h"
#include "ListNode.h"
#include <utility>
using namespace std;

template <typename T>
class LinkedList : public Indexed < T >
{
private:

	//points to the front of the linked list
	ListNode<T> *_front = nullptr;
	ListNode<T> *_end = nullptr;
	int _last_accessed_index = 0;
	ListNode<T> *_last_accessed_node = nullptr;

	//keeping track of size in a variable eliminates need to continually
	//count LL boxes.
	int _size = 0;


protected:
	ListNode<T> *getFront()
	{
		return _front;
	}

	ListNode<T> *getEnd()
	{
		return _end;
	}

	virtual ListNode<T> *createNode(T value)
	{
		return new ListNode < T > { value };
	}

	virtual void deleteNode(ListNode<T> *node)
	{
		delete node;
	}

	//can be used to return a ListNode<T> at a specific
	//index.
	ListNode<T> *getNodeAtIndex(int index)
	{
		//check to see if index is valid
		if (index < 0 || index >= getSize())
		{
			throw out_of_range("Invalid index.");
		}

		//which is closer: last accessed, the end, or the front?
		int counter = 0;
		ListNode<T> *starting_node = _front;
		if (index >= _last_accessed_index && _last_accessed_node != nullptr)
		{
			starting_node = _last_accessed_node;
			counter = _last_accessed_index;
		}
		if (index == _size - 1)
		{
			starting_node = _end;
			counter = _size - 1;
		}

		//keeps track of where we're at in our LL
		ListNode<T> *current = starting_node;
		while (counter < index && current != nullptr)
		{
			current = current->getNext();
			counter++;
		}

		_last_accessed_index = index;
		_last_accessed_node = current;

		//return desired node
		return current;
	}

	//AC note: cannot set last indexed node in const version
	//constant version of the above code
	const ListNode<T> *getNodeAtIndex(int index) const
	{
		//check to see if index is valid
		if (index < 0 || index >= getSize())
		{
			throw out_of_range("Invalid index.");
		}

		//which is closer: last accessed, the end, or the front?
		int counter = 0;
		ListNode<T> *starting_node = _front;
		if (index >= _last_accessed_index && _last_accessed_node != nullptr)
		{
			starting_node = _last_accessed_node;
			counter = _last_accessed_index;
		}
		if (index == _size - 1)
		{
			starting_node = _end;
			counter = _size - 1;
		}

		//keeps track of where we're at in our LL
		ListNode<T> *current = starting_node;
		while (counter < index && current != nullptr)
		{
			current = current->getNext();
			counter++;
		}

		return current;
	}

public:

#pragma region constructor - destructor


	LinkedList()
	{
		_front = nullptr;
		_end = _front;
	}

	//copy constructor
	//MA #1 TODO: Implement!
	LinkedList(const LinkedList<T> &other)
	{
		for (int i = 0; i < other.getSize(); i++)
		{
			addElement(other.getElementAt(i));
		}
	}

	//move constructor
	//MA #1 TODO: Implement!
	LinkedList(LinkedList<T> &&other)
	{
		_front = other._front;
		_end = other._end;
		_last_accessed_index = other._last_accessed_index;
		_last_accessed_node = other._last_accessed_node;
		_size = other._size;

		//reset pointers
		other._front = nullptr;
		other._end = nullptr;
		other._last_accessed_node = nullptr;
	}

	//initializer list constructor
	//MA #1 TODO: Implement!
	LinkedList(initializer_list<T> values)
	{
		for (auto item : values)
		{
			addElement(item);
		}
	}

	//Always remeber to clean up pointers in destructor!
	//MA #1 TODO: Implement!
	virtual ~LinkedList()
	{
		ListNode<T> *current = _front;
		while (current != nullptr)
		{
			ListNode<T> *temp = current->getNext();
			delete current;
			current = temp;
		}
	}
#pragma endregion

#pragma region Collection overrides

	//will return true if the LL is empty.
	virtual bool isEmpty() const
	{
		return _size == 0;
	}

	//returns the size of the LL.
	virtual int getSize() const
	{
		return _size;
	}

	//adds the supplied item to the end of our LL
	virtual void addElement(T value)
	{
		addElementAt(value, getSize());
	}
#pragma endregion

#pragma region Indexed overrides

	//returns the value at the specified index
	virtual T& getElementAt(int location)
	{
		//explicit way
		//ListNode<T> *result = getNodeAtIndex(location);
		//return result->getValue();

		//shortcut
		//this is called "method chaining" and can go on forever:
		//getNodeAtIndex(location)->getNext()->getNext()->getNext()
		///usually, not the best idea
		return getNodeAtIndex(location)->getValue();
	}

	virtual const T &getElementAt(int location) const
	{
		return getNodeAtIndex(location)->getValue();
	}

	//sets the value at the specified index
	virtual void setElementAt(T value, int location)
	{
		getNodeAtIndex(location)->setValue(value);
	}

	//adds the specified item at the specified index and shifts everything else
	//to the "right" by one.
	virtual void addElementAt(T value, int location)
	{
		ListNode<T> *new_value = createNode(value);

		//When adding to a LL, we have to consider two possibilities:
		//Option #1: are we adding this to the front?
		if (location == 0)
		{
			new_value->setNext(_front);
			_front = new_value;
		}
		else if (location == _size)
		{
			//adding to the end of the list?
			_end->setNext(new_value);
			_end = _end->getNext();
		}
		else
		{
			//Option #2: Adding somewhere else
			ListNode<T> *before = getNodeAtIndex(location - 1);
			new_value->setNext(before->getNext());
			before->setNext(new_value);
		}

		//is size 0
		if (_size == 0)
		{
			_end = _front;
		}

		//remember to increment size counter
		_size++;

	}

	//CLASS TODO
	//removes the element at the specified index.
	virtual void removeElementAt(int index)
	{
		//make sure index is in bounds
		if (index < 0 || index >= getSize())
		{
			throw out_of_range("Invalid index.");
		}

		//two possibilities:
		//Index is 0 (first item in LL)
		if (index == 0)
		{
			ListNode<T> *old_front = _front;
			_front = _front->getNext();
			deleteNode(old_front);
		}
		else
		{
			//Index is greater than 0 (not the first item in LL)
			ListNode<T> *before = getNodeAtIndex(index - 1);
			ListNode<T> *to_delete = before->getNext();
			before->setNext(to_delete->getNext());
			deleteNode(to_delete);

			//check to see if we removed the last element
			if (index == _size - 1)
			{
				_end = before;
			}
		}

		//is our size 1?
		if (_size == 1)
		{
			_end = _front;
		}

		//remember to decrement size
		_size--;
	}

#pragma endregion

#pragma region operator overloads

	/*
	for (int i = 0; i < other.getSize(); i++)
		{
			addElement(other.getElementAt(i));
		}
	}

	//move constructor
	//MA #1 TODO: Implement!
	LinkedList(LinkedList<T> &&other)
	{
		
	}*/

	//copy operator
	//MA #1 TODO: Implement!
	virtual LinkedList<T> &operator=(const LinkedList<T> &other)
	{
		//delete our elements
		while (getSize() > 0)
		{
			removeElementAt(0);
		}

		//add in other's elements
		for (int i = 0; i < other.getSize(); i++)
		{
			addElement(other.getElementAt(i));
		}

		return *this;
	}

	//move operator
	//MA #1 TODO: Implement!
	virtual LinkedList<T> &operator=(LinkedList<T> &&other)
	{
		//delete our elements
		while (getSize() > 0)
		{
			removeElementAt(0);
		}

		//grab other data
		_front = other._front;
		_end = other._end;
		_last_accessed_index = other._last_accessed_index;
		_last_accessed_node = other._last_accessed_node;
		_size = other._size;

		//reset pointers
		other._front = nullptr;
		other._end = nullptr;
		other._last_accessed_node = nullptr;

		return *this;
	}

#pragma endregion

};

#endif // !LINKED_LIST_H
