#ifndef STUDENT_HASHER_H
#define STUDENT_HASHER_H


#include "HasherBase.h"
#include <string>
using namespace std;

class StudentHasher : public HasherBase<string>
{
	//virtual int getHash(const string &item, int mod_by)
	//{
	//	//MA #4 TODO: IMPLEMENT!
	//	static const int InitialFNV = 2166136261U;
	//	static const int FNVMultiple = 16777619;

	//	long long hash = 0;

	//	hash = InitialFNV;

	//	for (int i = 0; i < item.length(); i++)
	//	{
	//		hash = hash ^ (item[i]);       /* xor  the low 8 bits */
	//		hash = hash * FNVMultiple;  /* multiply by the magic number */
	//	}
	//	return hash;
	//}

	virtual int getHash(const string &item, int mod_by)
	{
		static const int FNVMultiple = 16777619;

		int hash = 0;
		for (char ch : item)
		{
			hash += ch;
			hash = hash * FNVMultiple;

		}
		return hash & mod_by;
	}
};
#endif
