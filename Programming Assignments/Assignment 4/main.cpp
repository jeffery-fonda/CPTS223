#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <functional>
#include <queue>
#include "packet.h"
#include "message.h"
#include "graph.h"
#include "path.h"
#include "network.h"
#include "stringsplitter.h"


using namespace std;

int main(int argc, char *argv[])
{
	Packet packet{};
	Message message{};
	Graph graph{};
	Path path{};
	Network network{};
	StringSplitter splitter{};

	string filename;
	int source_node;
	int dest_node;
	string _message;

	//make the menu, get information
	cout << "Welcome to the Network Simulator!" << endl;
	cout << "Please enter a .txt file from which to build your network: ";
	cin >> filename;
	cout << "Please enter a source node for your message: ";
	cin >> source_node;
	cout << "Please enter a destination node for your message: ";
	cin >> dest_node;
	cout << "Please enter your message: " << endl;
	cin >> _message;

	//parse the file, create graph
	ifstream graph_file;
	graph_file.open(filename);
	vector <Vertex> _graph;

	for (int i = 0; !graph_file.eof(); i++)
	{
		//split each line with string splitter
		string line;
		getline(graph_file, line);
		vector<string> split_line;
		split_line = splitter.split(line, " ");

		//if only one element in vector, it's a new vertex.
		//if three elements in vector, it's edge information.
		if (split_line.size() == 1)
		{
			//make a new vertex
			Vertex vertex{};
			vertex.set_id(stoi(split_line[0]));

			//emplace it in the graph
			graph.add_vertex(vertex);
			_graph = graph.get_vertices();

			//if it matches our source, make it the starting_vertex
			if (vertex.get_id() == source_node)
			{
				message.set_starting_vertex(&vertex);
			}
			//if it matches our destination, make it the ending_vertex
			if (vertex.get_id() == dest_node)
			{
				message.set_ending_vertex(&vertex);
			}
		}

		
		else
		{
			//find the correct vertex and make changes to it

			int source = stoi(split_line[0]);
			int dest = stoi(split_line[1]);
			int weight = stoi(split_line[2]);

			_graph.at(source - 1).add_edge(&_graph.at(dest - 1), weight);

			graph.set_vertices(_graph);
		}
		
	}
	
	//for testing
	//cout << graph.get_vertices().size() << endl;

	

	Vertex source_vertex;
	for (Vertex vertex : graph.get_vertices())
	{
		if (vertex.get_id() == source_node)
		{
			source_vertex = vertex;
		}
	}

	graph.dijkstra(source_vertex);
	cout << endl;
	//graph.print_path();

	//create the packets and message

	queue<Packet> temp_message;
	for (char character : _message)
	{
		packet.set_value(character);
		temp_message.push(packet);
	}
	message.set_packets(temp_message);

	cout << "Here's what I know from my constructed graph:" << endl;
	cout << "There are " << graph.get_vertices().size() << "total vertices." << endl;
	cout << "Vertex, Number of adjacent vertices" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << graph.get_vertices().at(i).get_id() << ",    " << graph.get_vertices().at(i).get_edges().size() << endl;
	}
	cout << "My dijkstra's algorithm implementation is in the graph header file.";


	return 0;
}