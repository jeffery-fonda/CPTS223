#ifndef INDEXED_SORTER_H
#define INDEXED_SORTER_H

#include "ADTs/Indexed.h"

template <typename T>
class IndexedSorter
{
public:
	virtual Indexed<T>& sort(Indexed<T>& data) = 0;
};

#endif