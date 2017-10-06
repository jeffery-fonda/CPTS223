#include <cstdlib>
#include <iostream>
#include <string>
#include "ADTs\Heap.h"

void heapTests()
{
	Heap<int> pq{};
	pq.enqueue(10);
	pq.enqueue(9);
	pq.enqueue(8);
	pq.enqueue(7);
	pq.enqueue(6);
	pq.enqueue(5);
	pq.enqueue(4);
	pq.enqueue(3);
	pq.enqueue(2);
	pq.enqueue(1);

	while (pq.isEmpty() == false)
	{
		int top = pq.dequeue();
		cout << "Dequeue top: " << top << endl;
	}
}

int main(int argc, char* argv[])
{
	heapTests();
}