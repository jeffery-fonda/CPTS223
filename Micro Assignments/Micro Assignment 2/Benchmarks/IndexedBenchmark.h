#ifndef INDEXED_BENCHMARK_H
#define INDEXED_BENCHMARK_H
#include "ADTs\Indexed.h"

//easy mode RNG
#include "Misc\RandomNumberGenerator.h"

//for time benchmarks
#include <chrono>

using namespace std::chrono;

//Benchmark for basic queue operations
template <typename T>
class IndexedBenchmark
{
private:
	RandomNumberGenerator _rng;

public:
	IndexedBenchmark()
	{

	}

	//MA #2 TODO
	//Tests insert speed (beginning of structure) of supplied indexed ADT.
	long long insertAtEndTest(Indexed<T> &data, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//benchmark clock begins as soon as this line finishes
		start = system_clock::now();

		//This is where we test insert at end.
		for (int i = 0; i < num_trials; i++)
		{
			data.addElementAt(1, 0);
		}

		//end clock as soon as benchmark is complete
		end = system_clock::now();

		//return duration in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}

	//MA #2 TODO
	//Tests insert speed (end of structure) of supplied indexed ADT.
	long long insertAtBeginningTest(Indexed<T> &data, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//benchmark clock begins as soon as this line finishes
		start = system_clock::now();

		//This is where we insert at front.
		for (int i = 0; i < num_trials; i++)
		{
			data.addElement(0);
		}

		//end clock as soon as benchmark is complete
		end = system_clock::now();

		//return duration in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}

	//MA #2 TODO
	//Tests removal speed (end of structure) of supplied indexed ADT.
	long long removeAtEndTest(Indexed<T> &data, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//benchmark clock begins as soon as this line finishes
		start = system_clock::now();

		//This is where we delete a node at the end of the list.
		for (int i = 0; i < num_trials; i++)
		{
			data.removeElementAt(_rng.getRandomNumber());
		}

		//end clock as soon as benchmark is complete
		end = system_clock::now();

		//return duration in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}

	//MA #2 TODO
	//Tests removal speed (beginning of structure) of supplied indexed ADT.
	long long removeAtBeginningTest(Indexed<T> &data, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//benchmark clock begins as soon as this line finishes
		start = system_clock::now();

		//This is where we delete the first node.
		for (int i = 0; i < num_trials; i++)
		{
			data.removeElementAt(0);
		}

		//end clock as soon as benchmark is complete
		end = system_clock::now();

		//return duration in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}

	//MA #2 TODO
	//Tests find speed of supplied indexed ATD.  
	//Use _rng to randomly generate number to find.
	long long randomFindTest(Indexed<T> &data, int num_trials)
	{
		//set up clock variables
		system_clock::time_point start;
		system_clock::time_point end;

		//benchmark clock begins as soon as this line finishes
		start = system_clock::now();

		//This is where we find a node at the randomly generated time.
		for (int i = 0; i < num_trials; i++)
		{
			data.getElementAt(_rng.getRandomNumber());
		}

		//end clock as soon as benchmark is complete
		end = system_clock::now();

		//return duration in milliseconds
		return duration_cast<milliseconds>(end - start).count();
	}

};

#endif
