#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <functional>
#include <queue>
#include <unordered_map>

using namespace std;

class Vertex
{
private:
	int id;
	unordered_map < Vertex*, int > edges;
	int load_factor;
	int distance;
	bool known;

public:
	//constructor
	Vertex()
	{
		id = 0;
		load_factor = 0;
		distance = 100000;
		known = false;
	}

	//getters and setters
	
	int get_distance()
	{
		return distance;
	}

	void set_distance(int _distance)
	{
		distance = _distance;
	}

	bool is_known()
	{
		return known;
	}

	void set_known(bool _known)
	{
		known = _known;
	}

	int get_id()
	{
		return id;
	}

	void set_id(int _id)
	{
		id = _id;
	}

	unordered_map<Vertex*, int> get_edges ()
	{
		return edges;
	}

	void set_edges(unordered_map<Vertex*, int> _edges)
	{
		edges = _edges;
	}

	int get_load_factor()
	{
		return load_factor;
	}

	void set_load_factor(int _load_factor)
	{
		load_factor = _load_factor;
	}

	void add_edge(Vertex* _vertex, int weight)
	{
		edges.emplace(_vertex, weight);
	}
};

#endif;