#include "ADTs\HashTables\HasherFactory.h"
#include "ADTs\HashTables\LinearHashTable.h"
#include "ADTs\HashTables\BucketHashTable.h"
#include "ADTs\HashTables\DoubleHashTable.h"
#include "ADTs\HashTables\QuadraticHashTable.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

long long hashInsertBench(HashTableBase<string, string> &ht, int num_inputs)
{
	//set up clock variables
	system_clock::time_point start;
	system_clock::time_point end;

	//benchmark clock begins as soon as this line finishes
	start = system_clock::now();

	//enqueue data
	for (int i = 0; i < num_inputs; i++)
	{
		string str = to_string(i);
		ht.addElement(str, str);
	}

	//end clock as soon as benchmark is complete
	end = system_clock::now();

	//return duration in milliseconds
	return duration_cast<milliseconds>(end - start).count();
}

void compareHashTables(HashTableBase<string, string> &base, HashTableBase<string, string> &student, string name)
{
	int num_inserts = 5000;
	long long base_speed = hashInsertBench(base, num_inserts);
	long long student_speed = hashInsertBench(student, num_inserts);
	cout << "Base hash result: " << base_speed << endl;
	cout << "Student hash result: " << student_speed << endl;
	if (student_speed < base_speed * 0.6)
	{
		cout << "Hash function on " << name << " Hashtable is fast!" << endl; 
	}
	else
	{
		cout << "Hash function on " << name << " Hashtable not fast enough!" << endl;
	}
}

int main(int argc, char *argv[])
{
	LinearHashTable<string, string> linear_base{ new SimpleStringHasher{} };
	QuadraticHashTable<string, string> quadratic_base{ new SimpleStringHasher{} };
	DoubleHashTable<string, string> doubleHash_base{ new SimpleStringHasher{} };
	BucketHashTable<string, string> bucket_base{ new SimpleStringHasher{} };

	LinearHashTable<string, string> linear_student{ new StudentHasher{} };
	QuadraticHashTable<string, string> quadratic_student{ new StudentHasher{} };
	DoubleHashTable<string, string> doubleHash_student{ new StudentHasher{} };
	BucketHashTable<string, string> bucket_student{ new StudentHasher{} };

	/*unordered_map<string, string>test{};

	test["a"] = "b";
	test["c"] = "d";*/

	//compare hashing algorithms.  Student hasher must be 40% faster
	compareHashTables(linear_base, linear_student, "Linear");
	compareHashTables(quadratic_base, quadratic_student, "Quadratic");
	compareHashTables(doubleHash_base, doubleHash_student, "Double");
	compareHashTables(bucket_base, bucket_student, "Bucket");

}