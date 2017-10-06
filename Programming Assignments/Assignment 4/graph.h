#ifndef GRAPH_H
#define GRAPH_H

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
#include "path.h"

using namespace std;

class Graph
{
private: 
	//unordered map with vertices and distance from the starting vertex
	vector <Vertex> vertices;
	vector <Vertex> unknown_vertices;
	Path path{};

public:
	//find vertex in vertices with the smallest distance
	Vertex find_smallest()
	{
		Vertex smallest;
		smallest.set_distance(10000);
		int flag;

		for (int i = 0; i < unknown_vertices.size(); i++)
		{
			if (vertices.at(i).get_distance() <= smallest.get_distance())
			{
				smallest = unknown_vertices.at(i);
				flag = i;
			}
		}

		unknown_vertices.erase(unknown_vertices.begin()+flag);
		return smallest;
	}

	//print path
	void print_path()
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			cout << vertices.front().get_id();
			vertices.pop_back();
		}
	}
	//getters and setters for vertices

	vector <Vertex> get_vertices()
	{
		return vertices;
	}

	void set_vertices(vector <Vertex> _vertices)
	{
		vertices = _vertices;
	}

	void add_vertex(Vertex _vertex)
	{
		vertices.push_back(_vertex);
	}

	void dijkstra(Vertex starting_vertex)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			//my program initially stores vertices in the vertex in spot (id - 1).
			unknown_vertices = vertices;

			if (vertices[i].get_id() == starting_vertex.get_id())
				vertices[i].set_distance(0);
			
			else
				vertices[i].set_distance(10000000);
			
			vertices[i].set_known(false);
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			//while there is an unknown distance vertex
			if (vertices[i].is_known() == false)
			{
				//TODO: find smallest unknown distance vertex
				Vertex v = find_smallest();
				v.set_known(true);

				//for every vertex adjacent to this vertex
				for (pair<Vertex*, int> edge : v.get_edges())
				{
					//if the vertex isn't known
					if (edge.first->is_known() == false)
					{
						//calculate the weight using Adam's note on dijkstra's algorithm
						int weight = edge.second * edge.first->get_load_factor();

						if (v.get_distance() + weight < edge.first->get_distance())
						{
							edge.first->set_distance(v.get_distance() + weight);
							path.add_vertex(edge.first);
						}
					}
				}
			}
		}

		
	}

};

#endif