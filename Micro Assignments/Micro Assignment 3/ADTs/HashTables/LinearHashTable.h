#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include "HashTableBase.h"

template <typename Key, typename Value>
class LinearHashTable : public HashTableBase<Key, Value>
{
protected:

	//determines whether or not we need to resize
	//to turn off resize, just always return false
	virtual bool needsResize()
	{
		//linear probing seems to get worse after a load factor of about 70%
		if (_number_of_elements > (.7 * _primes[_local_prime_index]))
		{
			return true;
		}
		return false;
	}

	//called to check to see if we need to resize
	virtual void resizeCheck()
	{
		//Right now, resize when load factor > .75; it might be worth it to experiemnt with 
		//this value for different kinds of hashtables
		if (needsResize())
		{
			_local_prime_index++;

			HasherBase<Key> *hasher = HasherFactory::copyHasher<Key>(*_hasher);
			LinearHashTable<Key, Value> new_hash{ hasher, _primes[_local_prime_index] };

			for (auto item : _items)
			{
				if (item.isEmpty() == false)
				{
					//add to new hash table 
					new_hash.addElement(item.getKey(), item.getValue());
				}
			}

			//MOVE IS COOL!
			*this = move(new_hash);
		}
	}

public:

	LinearHashTable(HasherBase<Key> *hasher, int number_of_elements = 11)
		: HashTableBase(hasher, number_of_elements)
	{

	}

	LinearHashTable(LinearHashTable<Key, Value> &other)
		: HashTableBase(other)
	{

	}

	LinearHashTable(LinearHashTable<Key, Value> &&other)
		: HashTableBase(other)
	{

	}

	LinearHashTable & operator=(LinearHashTable<Key, Value> &other)
	{
		HashTableBase::operator=(other);
		return *this;
	}

	LinearHashTable & operator=(LinearHashTable<Key, Value> &&other)
	{
		HashTableBase::operator=(other);
		return *this;
	}

	//concrete implementation for parent's addElement method
	virtual void addElement(const Key &key, const Value &value)
	{
		//check for size restrictions
		resizeCheck();

		//calculate hash based on key
		int hash = HashTableBase::getHash(key);

		//MA #3 TODO: find empty slot to insert (update hash variable as necessary)
		while (_items[hash].isEmpty() == false) // checking to see if spot is empty
		{
			hash++; // keep going until spot is empty
			if (hash > _items.size() - 1)
			{
				hash = 0; // find empty spot
			}
		}

		// insert stuff into spot in table
		_items[hash].setValue(value);
		_items[hash].setKey(key);
		_items[hash].setIsEmpty(false);

		//remember how many things we're presently storing
		_number_of_elements++;
	}

	//removes supplied key from hash table
	virtual void removeElement(Key key)
	{
		//calculate hash
		int hash = HashTableBase::getHash(key);

		//MA #3 TODO: find slot to remove.  Remember to check for infinite loop!
		while (_items[hash].getKey() != key)
		{
			hash++;
			if (hash > _items.size() - 1) // check to see if at end of table
			{
				hash = 0;
			}
		}

		_items[hash].setIsEmpty(true); // set spot empty

		//decrement hashtable size
		_number_of_elements--;
	}

	//returns true if the key is contained in the hash table
	virtual bool containsElement(Key key)
	{
		int hash = HashTableBase::getHash(key);
		HashItem<Key, Value> *slot = &_items[hash];
		
		//Turned off, no hints! :)
		throw exception("function not implemented");
	}

	//returns the item pointed to by key
	virtual Value &getElement(string key)
	{
		int hash = HashTableBase::getHash(key);
		HashItem<Key, Value> *slot = &_items[hash];

		//Turned off, no hints! :)
		throw exception("Key not found.");
	}
};

#endif