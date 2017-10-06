#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <functional>
#include <queue>
#include <unordered_map>
#include "vertex.h"
#include "packet.h"

using namespace std;

class Message
{
private: 
	queue<Packet> packets;
	Vertex* starting_vertex;
	Vertex* ending_vertex;

public:
	queue<Packet> get_packets()
	{
		return packets;
	}

	void set_packets(queue<Packet> _packets)
	{
		packets = _packets;
	}

	Vertex* get_starting_vertex()
	{
		return starting_vertex;
	}

	void set_starting_vertex(Vertex* _vertex)
	{
		starting_vertex = _vertex;
	}

	Vertex* get_ending_vertex()
	{
		return ending_vertex;
	}

	void set_ending_vertex(Vertex* _vertex)
	{
		ending_vertex = _vertex;
	}
};

#endif