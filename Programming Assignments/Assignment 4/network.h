#ifndef NETWORK_H
#define NETWORK_H

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

class Network : public Graph
{
private:
	Graph graph;
	int tick_count;
	Message message;
	//more?

public:
	void tick()
	{
		//1. If the message still has packets that need to be transmitted, queue the next packet for transmission at the starting location : 
		if (message.get_packets().size() != 0)
		{ 
			//a.Compute the shortest route between the starting location and the packet's final destination using Dijkstra's Algorithm(See note on Dijkstra's Algorithm). 
			//b. Determine the next intermediary transmission node.  On a Path = v1, v2, v3, ... , vn where v1 = starting location, the next intermediary node would be v2. 
			//c. The arrival time of the packet at v2 is determined by the natural, unmodified weight of the link between v1 and v2 and the load factor of v2.  Thus wait = weight * load(v2).  Queue the packet's arrival at the appropriate time in the future.Note that a packet whose transit time is 1 should arrive at the destination node during the following loop.In other words, it should be delivered during step #2. 
			//d.Because v1 and v2 are communicating, increase the load factor of each node by 1. 
		}
		
		//2. For each packet presently in the network : 
		//a.Decrement the packet's expected arrival time 
		//b. If the packet's arrival time is less than or equal to 0, the packet is considered to have arrived at its next destination.
		//i.Decrease the load factor of both the source and destination nodes by 1 
		//ii.If the packet has not reached its final destination, schedule another transmission using the method described in #1a - 1d.  Be sure to alter the nodes that are transmitting the packet.For example, if the packet just arrived at v2 from v1, the next transmission would occur between v2 and v3.
		//iii.If the packet has reached its final destination, put the packet in a list of completed packets(this will be used to display the final transmission results)
	}
	//more
};

#endif;