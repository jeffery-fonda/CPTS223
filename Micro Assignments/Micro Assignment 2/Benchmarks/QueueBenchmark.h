#ifndef QUEUE_BENCHMARK_H
#define QUEUE_BENCHMARK_H
#include "ADTs\Queue.h"

//easy mode RNG
#include "Misc\RandomNumberGenerator.h"

//for time benchmarks
#include <chrono>

using namespace std::chrono;

//Benchmark for basic queue operations
template <typename T>
class QueueBenchmark 
{
private:
	RandomNumberGenerator _rng;

public:
	QueueBenchmark()
	{

	}

	//Tests enqueue speed of supplied queue
	long long enqueueTest(Queue<T> &some_queue, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//benchmark clock begins as soon as this line finishes
		start = system_clock::now();

		//enqueue data
		for (int i = 0; i < num_trials; i++)
		{
			some_queue.enqueue(_rng.getRandomNumber());
		}

		//end clock as soon as benchmark is complete
		end = system_clock::now();

		//return duration in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}

	//Tests dequeue speed of supplied queue
	long long dequeueTest(Queue<T> &some_queue, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//begin benchmark
		start = system_clock::now();

		//dequeue data
		for (int i = 0; i < num_trials; i++)
		{
			some_queue.dequeue();
		}

		//end benchmark
		end = system_clock::now();

		//return time in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}
};

#endif
