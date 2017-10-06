#include <iostream>
#include <cstdlib>
#include <string>
#include "ADTs\Array.h"
#include "ADTs\Vector.h"
#include "ADTs\Indexed.h"
#include "ADTs\CircularQueue.h"
#include "ADTs\QueueAdapter.h"
#include "ADTs\LinkedList.h"
#include "Benchmarks\QueueBenchmark.h"
#include "Benchmarks\IndexedBenchmark.h"
#include "MISC\RandomNumberGenerator.h"

using namespace std;

//test queue structures
void runQueueBenchmarks(Queue<int> &some_queue, int num_items, string queueType)
{
	QueueBenchmark<int> bm{};
	cout << "Insert " << num_items << " elements in " << queueType << " queue: " << bm.enqueueTest(some_queue, num_items) << endl;
	cout << "Removing " << num_items << " elements in " << queueType << " queue: " << bm.dequeueTest(some_queue, num_items) << endl;
}

void runIndexedBenchmarks(Indexed<int> &data, int num_items, string indexedType)
{
	IndexedBenchmark<int> bm{};
	//RandomNumberGenerator random{}; need something to randomly generate the find element at random location
	cout << "Insert at end " << indexedType << " indexed: " << bm.insertAtEndTest(data, num_items) << endl;
	cout << "Insert at front " << indexedType << " indexed: " << bm.insertAtBeginningTest(data, num_items) << endl;
	cout << "Remove at end " << indexedType << " indexed: " << bm.removeAtEndTest(data, num_items) << endl;
	cout << "Remove at front " << indexedType << " indexed: " << bm.removeAtBeginningTest(data, num_items) << endl;
	//cout << "Find element " << random.getRandomNumber << " in " << indexedType << bm.randomFindTest(date, num_items) << endl;
}

int main(int argc, char *argv[])
{
	//*** EXAMPLE Benchmarks for Queue ***\\

	//create queue structures
	QueueAdapter<int> vector_queue{ new Vector<int>{} };
	QueueAdapter<int> ll_queue{ new LinkedList<int>{} };
	CircularQueue<int> circular{ };
	//Vector<int> ll_index{ LinkedList<int>{} };

	//test structures
	runQueueBenchmarks(vector_queue, 100000, "vector");
	runQueueBenchmarks(ll_queue, 100000, "linked list");
	runQueueBenchmarks(circular, 100000, "circular");
	//runIndexedBenchmarks(ll_index, 100000, "indexed");
}