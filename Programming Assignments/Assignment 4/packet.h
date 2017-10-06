#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <functional>
#include <queue>
#include "vertex.h"

using namespace std;

class Packet
{
private:
	char value;
	int order;
	int current_wait;
	Vertex* destination;
	Vertex* previous_location;
	Vertex* next_hop;

public:
	//getters and setters

	char get_value()
	{
		return value;
	}

	void set_value(char _value)
	{
		value = _value;
	}

	int get_order()
	{
		return order;
	}

	void set_order(int _order)
	{
		order = _order;
	}

	int get_current_wait()
	{
		return current_wait;
	}

	void set_current_wait(int _current_wait)
	{
		current_wait = _current_wait;
	}

	Vertex* get_destination()
	{
		return destination;
	}

	void set_destination(Vertex* _destination)
	{
		destination = _destination;
	}

	Vertex* get_previous_location()
	{
		return previous_location;
	}

	void set_previous_location(Vertex* _previous_location)
	{
		previous_location = _previous_location;
	}

	Vertex* get_next_hop()
	{
		return next_hop;
	}

	void set_next_hop(Vertex* _next_hop)
	{
		next_hop = _next_hop;
	}
};


#endif
