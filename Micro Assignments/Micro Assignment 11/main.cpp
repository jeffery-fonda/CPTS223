#include "DisjointSet.h"
#include "RandomNumberGenerator.h"
#include <iostream>
#include <string>
#include <queue>
#include <functional> //for min PQ
#include <chrono>

using namespace chrono;
using namespace std;

//Simple benchmark for disjoint sets
static long long disjointSetBenchmark(DisjointSet<int> &data, int loop_count)
{
	system_clock::time_point start;
	system_clock::time_point end;
	RandomNumberGenerator rng{};
	start = system_clock::now();

	for (int i = 0; i < loop_count; i++)
	{
		int left = rng.getRandomNumber(1, 10000);
		int right = rng.getRandomNumber(1, 10000);
		data.union_with(left, right);
	}

	for (int i = 0; i < loop_count * 2; i++)
	{
		int left = rng.getRandomNumber(1, 10000);
		data.find(left);
	}

	end = system_clock::now();
	return duration_cast<milliseconds>(end - start).count();
}

//basic test function for disjoint sets
void disjointTest()
{
	DisjointSet<char> items{};
	
	//add a bunch of starter sets
	for (char i = 'a'; i < 'k'; i++)
	{
		//"find" operation will insert the item into the set if it doesn't exist
		items.find(i);
	}

	//now, perform some unions
	items.union_with('a', 'b');
	items.union_with('c', 'd');
	items.union_with('e', 'f');
	items.union_with('g', 'h');

	//basic tests
	cout << "a in same set as b (expected True): " << ((*items.find('a')) == (*items.find('b'))) << endl;
	cout << "c in same set as a (expected False): " << ((*items.find('a')) == (*items.find('c'))) << endl;

	//do some more unions
	items.union_with('b', 'd');

	//recheck
	cout << "c in same set as a (expected True): " << ((*items.find('a')) == (*items.find('c'))) << endl;

	//get all roots
	vector<char> roots = items.getRoots();
	cout << "Set roots (expected i, a, e, g, j - order not important): " << endl;
	for (auto ch : roots)
	{
		cout << ch << " ";
	}
	cout << endl;
}

int main(void)
{	
	DisjointSet<int> without_compression{};
	DisjointSet<int> with_compression{};
	with_compression.use_path_compression = true;

	disjointTest();

	//uncomment for benchmark
	//cout << "With compression: " << disjointSetBenchmark(with_compression, 50000) << "ms." << endl;
	//cout << "Without compression: " << disjointSetBenchmark(without_compression, 50000) << "ms." << endl;
	
}