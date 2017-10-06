#ifndef PATH_H
#define PATH_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <functional>
#include <queue>
#include "vertex.h"
#include "graph.h"
#include <stack>

using namespace std;

class Path 
{
private:
	stack<Vertex*> vertices;
	int distance_traveled;

public:
	//getters and setters

	stack<Vertex*> get_vertices()
	{
		return vertices;
	}

	void add_vertex(Vertex* new_vertex)
	{
		vertices.push(new_vertex);
	}

	void set_vertices(stack<Vertex*> _vertices)
	{
		vertices = _vertices;
	}

	int get_distance_traveled()
	{
		return distance_traveled;
	}

	void set_distance_traveled(int _distance)
	{
		distance_traveled = _distance;
	}

	

};

#endif