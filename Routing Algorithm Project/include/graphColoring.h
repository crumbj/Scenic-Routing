//********************************************************************
// File name:  graphColoring.h
// Author:     Megan DeYoung
// Date:       1/6/2021
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    define the GraphColoring algorithm class
//********************************************************************
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <map>
#include "graph.h"


class GraphColoring {
public:
	GraphColoring(Graph * graph);
	~GraphColoring();
	void dfsCycle(int nodeID1, int nodeID2, int colored[], int marked[],
			int parents[], int &cycleNumber);
	std::vector<std::vector<std::string>> createCycleList(int marked[],
			int &cycleNumber);
	std::vector<std::vector<std::string>> getCycleList()
			{return mCycleList;};
	void printCycleList();


private:
	Graph *mpOriginalGraph;
	std::vector<std::vector<std::string>> mCycleList;
};
