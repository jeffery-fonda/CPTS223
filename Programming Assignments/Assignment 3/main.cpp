//Program flow:

//1. open files for reading
//2. read first line to get total cpus
//3. read in job number, cpus required, and duration into a struct
//4. for each tick (seconds):
//		1. if the list of jobs is not empty, add the next job to the queue
//		2. if the queue is not empty:
//			a. find job with shortest duration
//				if job.CPUs <= totalCPUs, start job
//		3. for each job happening now:
//			a. do one tick work of work on job
//			b. if job is done:
//				remove job from current jobs
//				free cpus that job was using

#include "Heap.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
	string file_name = "";
	string line = "";
	vector<Job> vector_of_jobs;
	vector<string> input_files;

	ofstream output_file{ "result.csv" };

	if (argc != 1) //if there are files in the command line, add them to the vector
	{
		for (int i = 1; i < argc; i++) //step through argc to see how many files there are
		{
			input_files.emplace(input_files.begin(), argv[i]); //get file names
		}
	}
	else //no files present in command line, get them
	{
		string input_file_name;
		cout << "Please enter filename to use: ";
		cin >> input_file_name;
		input_files.emplace(input_files.begin(), input_file_name); //add them to the vector
	}

	for (int i = 0; i < input_files.size(); i++) //step through vector of files, can execute more than one file
	{
		ifstream input_file{input_files[i]}; //open file for reading

		if (input_file.is_open() == true) //if the file opens successfully
		{
			//if the file was opened, we can begin reading
			//read in how many CPUs we will have
			getline(input_file, line); //read line in file
			int total_CPUs = stoi(line, nullptr, 10); //total CPUs

			cout << "We have " << total_CPUs << " CPUs to use" << endl << endl;
			system("pause");

			while (input_file.good() == true) //going through and reading each line in the file
			{
				getline(input_file, line); //read line in file

				if (line != "NULL") //random case if there is a NULL job
				{
					vector<string> line_details = StringSplitter::split(line, " "); //remove the spaces
					Job job; //declare a struct of Job
					job.name = line_details[0]; //add name of job to struct
					job.CPUs = stoi(line_details[1], nullptr, 10); //add CPUs required to struct
					job.duration = stoi(line_details[2], nullptr, 10); //add duration to struct

					vector_of_jobs.push_back(job); //add each job to a vector
				}
				else //if there is a NULL job, just skip that line
				{
					continue;
				}

			}

			cout << "All jobs have been read in, ready to execute." << endl;

			Heap<Job> job_heap{}; //create my heap of jobs
			int available_CPUs = total_CPUs; //will be used to keep track of available CPUs
			vector<Job> active_jobs; //make a vector to keep track of active jobs
			int j = 0;

			do
			{
				j++;
				int k;
				int location;

				cout << endl << "*** Tick: " << j << " ***" << endl << endl;
				cout << "Processing job file..." << endl;

				if (vector_of_jobs.empty() == true) //if no more jobs in file, just keep going
				{
					cout << "There are no more jobs in the list." << endl;
				}
				if (vector_of_jobs.empty() == false) //if jobs in file, do this
				{
					vector_of_jobs[0].time_started = j; //make note of what tick the job started at
					job_heap.enqueue(vector_of_jobs[0]); //add that job to the heap
					//job_heap.adjustHeap(0);
					cout << "The next job in the list is: " << vector_of_jobs[0].name << endl;
					vector_of_jobs.erase(vector_of_jobs.begin()); //remove that job from the vector
					cout << "Adding job to jobs queue." << endl;
				}

				if (job_heap.isEmpty() == false && (job_heap.getFirst().CPUs <= available_CPUs)) //if there are available CPUs, do this
				{
					available_CPUs = available_CPUs - job_heap.getFirst().CPUs; //subtract the required CPUs from the available CPUs
					active_jobs.push_back(job_heap.dequeue()); //dequeue the item and add it to the active jobs vector
				}
				if (job_heap.isEmpty() == false && (job_heap.getFirst().CPUs > available_CPUs)) //if not enough CPUs available, do this
				{
					cout << endl << "Not enough resources. Needed: " << job_heap.getFirst().CPUs << " Available: " << available_CPUs << endl;
				}

				if (job_heap.getFirst().CPUs > total_CPUs) //guard code for if there is a job that requires more than the total CPUs
				{
					cout << "Error! Not enough CPUs in cluster to run job. Exiting." << endl;
					exit(0);
				}

				cout << endl << "Processing job queue." << endl;
				cout << "Current number of scheduled jobs: " << active_jobs.size() << endl;
				for (int m = 0; m < active_jobs.size(); m++) //this is where we put in work (on the jobs)
				{
					active_jobs[m].duration--; //decrease the duration for each tick of each job
					
					if (active_jobs[m].duration == 0) //if there is a job in the active jobs with duartion 0, remove it from active jobs
					{
						available_CPUs = available_CPUs + active_jobs[m].CPUs; //free resources
						location = m;
						cout << endl << "Job: " << active_jobs[m].name << " has been completed, freeing resources." << endl << endl;
						active_jobs[m].time_ended = j; //make note of how long it took job to execute
						output_file << active_jobs[m].name << ", " << active_jobs[m].time_started << ", " << active_jobs[m].time_ended << ", "
							<< "Total time to execute: " << (active_jobs[m].time_ended - active_jobs[m].time_started) << endl; //write that stuff to the details file
						active_jobs.erase(active_jobs.begin() + location); //finally remove job from active job vector because it is done
					}
				}

				//system("pause");

			} while (!(active_jobs.empty() == true && (job_heap.isEmpty() == true) && (vector_of_jobs.empty() == true)));

		}
		else
		{
			//file wasn't able to be opened, exit the program
			cout << "Error: File Cannot Be Opened" << endl;
			exit(0);
		}
	}

	output_file.close(); //close output file
}