//*****************************************************************************
// File name:  kruskal.h
// Author:     Megan DeYoung
// Date:       11/18/2020
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    Create the the functionality needed for Kruskal's algorithm
//*****************************************************************************

#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "hNode.h"
#include "edge.h"
#include "graph.h"


class Kruskal {
	public:
		Kruskal(Graph * graph, Graph *MST);
		~Kruskal();
		void negateAllWeights();
		void sortEdgesLowToHigh(std::vector<Edge *> &edgeList);
		void printMSTAdjList();
		void useKruskal();
		int findSet(int i, int *parentList);
		void makeUnion(int u, int v, int *parentList);
		void printEdges(std::vector<Edge *> pEdgeList);

	private:
		Graph *mpOriginalGraph;
		Graph *mpMST; // maximum spanning tree
};


