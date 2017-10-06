#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "IndexedSorter.h"
#include "ADTs/Vector.h"

#include <utility>

template <typename T>
class QuickSort : public IndexedSorter<T>
{
private:
	
	//MA #9 Optional: implement recursive solution
	//Received help from Megan in tutoring center
	void sortHelper(Indexed<T> &data, int start_bound, int end_bound)
	{
		if (start_bound < end_bound) //making sure array has at least one element
		{
			int tempData = objectSort(data, start_bound, end_bound); //need to create a temp place to store beginning/end data

			sortHelper(data, start_bound, tempData - 1); //sort smaller array
			sortHelper(data, tempData + 1, end_bound); //sort larger array
		}
	}

	T objectSort(Indexed<T>& data, int start_bound, int end_bound)
	//Received help from Megan in tutoring center
	{
		T index = start_bound; //create the index
		T pivot = data.getElementAt(start_bound); //create the pivot

		for (int position = start_bound + 1; position <= end_bound; position++)
		{
			if (pivot < data.getElementAt(position))
			{
				swap(data.getElementAt(index), data.getElementAt(index + 1)); //swap data smaller
				swap(data.getElementAt(index + 1), data.getElementAt(position)); //swap data larger
			}
			index++;
		}
		return index;
	}

public:

	//MA #9 TODO: Implement
	//Received help from Megan in tutoring center
	virtual Indexed<T>& sort(Indexed<T>& data)
	{
		
		sortHelper(data, 0, data.getSize() - 1); //call sortHelper to do the sorting
		return data;
	}

	
};

#endif