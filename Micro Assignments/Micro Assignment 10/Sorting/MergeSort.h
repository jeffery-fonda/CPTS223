#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "IndexedSorter.h"
#include "ADTs/Vector.h"

#include <vector>

template <typename T>
class MergeSort : public IndexedSorter<T>
{
private:

public:

	//Helper function to merge array
	void merge(Indexed<T>& data, Vector<T>& array1, Vector<T>& array2) 
	{
		int i, j, k;

		for (i = 0, j = 0, k = 0; i < array1.getSize() && j < array2.getSize(); k++) 
		{
			if (array1.getElementAt(i) <= array2.getElementAt(j)) 
			{
				data.removeElementAt(array1.getElementAt(i));
				i++;
			}
			else if (array1.getElementAt(i) > array2.getElementAt(j)) 
			{
				data.removeElementAt(array2.getElementAt(j));
				j++;
			}
			k++;
		}

		while (i < array1.getSize()) 
		{
			data.removeElementAt(array1.getElementAt(i));
			i++;
		}

		while (j < array2.getSize()) 
		{
			data.removeElementAt(array2.getElementAt(j));
			j++;
		}
	}

	//MA #10 TODO: IMPLEMENT!
	virtual Indexed<T>& sort(Indexed<T>& data)
	{
		if (1 < (data.getSize() - 1)) 
		{
			Vector<T> array1{ (data.getElementAt(0), (data.getElementAt(0) + data.getSize()) / 2) };
			sort(array1);
			Vector<T> array2{ ((data.getElementAt(0) + data.getSize()) / 2, (data.getSize() - 1)) };
			sort(array2);
			merge(data, array1, array2);
		}

		return data;
	}


};

#endif