#include <cstdio>
#include <string>
#include <iostream>
#include <chrono>

#include "ADTs\Vector.h"
#include "Sorting\BubbleSort.h"
#include "Sorting\InsertionSort.h"
#include "Sorting\SelectionSort.h"
#include "Sorting\QuickSort.h"
#include "RandomNumberGenerator.h"

using namespace std;
using namespace std::chrono;
long long indexedBenchmark(IndexedSorter<int> &sorter, Indexed<int> &data)
{
	//set up clock variables
	system_clock::time_point start;
	system_clock::time_point end;

	//benchmark clock begins as soon as this line finishes
	start = system_clock::now();

	//sort data
	sorter.sort(data);

	//end clock as soon as benchmark is complete
	end = system_clock::now();

	//return duration in milliseconds
	return duration_cast<milliseconds>(end - start).count();
}

long long runBenchmark(string sort_name, IndexedSorter<int> &sorter, Vector<int> &data)
{
	//copy values into temp array
	Vector<int> temp{data};
	cout << "Using " << sort_name << " to sort " << data.getSize() << " elements..." << endl;
	long long result = indexedBenchmark(sorter, temp);
	cout << "Result: " << result << "ms" << endl;
	return result;
}

int main(int argc, char *argv[])
{
	//generate large list of number
	RandomNumberGenerator rng{};
	Vector<int> numbers_base{};

	for (int i = 0; i < 3000; i++)
	{
		numbers_base.addElement(rng.getRandomNumber());
	}

	//instantiate sorters
	InsertionSort<int> insertion{};
	BubbleSort<int> bubble{};
	SelectionSort<int> selection{};
	QuickSort<int> quick{};

	//run benchmarks
	runBenchmark("insertion", insertion, numbers_base);
	runBenchmark("bubble", bubble, numbers_base);
	runBenchmark("selection", selection, numbers_base);
	runBenchmark("quick sort", quick, numbers_base);

}