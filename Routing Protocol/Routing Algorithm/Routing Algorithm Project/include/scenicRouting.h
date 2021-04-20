//*****************************************************************************
// File name:  scenicRouting.h
// Author:     Megan DeYoung
// Date:       1/12/2020
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    helper functions to combine all of the algorithms into the
//						 scenic routing algorithm
//*****************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "..//include//graph.h"
#include "..//include//kruskal.h"
#include "..//include//graphColoring.h"

void readGraphFromFile(Graph *pGraph, std::string fileName, int &numNodes,
		int &numEdges);
void initCycleList(GraphColoring *pGraphColoring, int numEdges,
		const int MAX_LOOPS);
void initMST(Kruskal *pKruskal);
std::vector<std::string> getPath(Graph *pMST, Graph *pOriginalGraph,
		std::string srcNodeName, std::string destNodeName, GraphColoring *pGP);
std::vector<std::string> getLoop(std::string srcNodeName,
			std::string destNodeName, GraphColoring *pGraphColoring);
void printPathWithCost(std::vector<std::string> path, Graph *pOriginalGraph);

