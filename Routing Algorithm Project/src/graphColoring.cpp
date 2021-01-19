//*****************************************************************************
// File name:  GraphColoring.cpp
// Author:     Megan DeYoung
// Date:       1/6/2021
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    implement graph coloring algorithm class functions
//*****************************************************************************

#include "..//include//graphColoring.h"

//********************************************************************
// Method:			GraphColoring
//
// Description: initialize member variables (constructor)
//
// Parameters:  graph - the graph to perform the algorithm on
//
// Returned:    none
//
//********************************************************************
GraphColoring::GraphColoring(Graph * graph){
	mpOriginalGraph = graph;
}
//********************************************************************
// Method:			~GraphColoring
//
// Description: free memory of member variables (destructor)
//
// Parameters:  graph - the graph to perform the algorithm on
//
// Returned:    none
//
//********************************************************************
GraphColoring::~GraphColoring(){

}
//********************************************************************
// Method:			dfsCycle
//
// Description: detect all the cycles in the graph using depth first
//							search and the adjacency list of the graph
//
// Parameters:  u - id number of the src node
//							p - id number of the dest node
//							colored - keep track of the color of a node
//												(node id is the index of the array)
//							marked  - nodes marked for a found cycle
//							cycleNumber - number used to keep track of the
//														current cycle the nodes are a part of
//							parent - keep track of the parent node for the
//											 node at index "node ID"
//
// Returned:    none
//
//********************************************************************
void GraphColoring::dfsCycle(int u, int p, int colored[],
			int marked[], int parents[], int &cycleNumber){


	const int SEEN = 1;
	const int COLORED = 2;
	std::vector<Node *> allNodes = mpOriginalGraph->getAllNodes();
	std::string uName = mpOriginalGraph->getNode(u)->getName();
	std::map <std::string, std::vector<Edge *>> adjList
				= mpOriginalGraph->getList();

	// the node has been visted completely
	if (COLORED == colored[u] ){
		return;
	}

	// the node has been seen (partially visited) (CYCLE DETECTED)
	// backtrack based on parents to find the complete cycle
	if (SEEN == colored[u]){
		cycleNumber++;
		int current = p;
		marked[current] = cycleNumber;

		//backtrack through the nodes in the current cycle
		while (current != u){
			current = parents[current];
			marked[current] = cycleNumber;
		}

		return;
	}

	parents[u] = p;

	//node has just been seen
	colored[u] = SEEN;

	//depth first search on the adjacencyList
	//current vector of edges
	//traverse vector of edges at adjList[u]

	for (Edge * it : adjList[uName]){
		int leftNodeID = it->getLeftNode()->getNodeID();
		int rightNodeID = it->getRightNode()->getNodeID();

		// if the node has not been previously visited
		if (leftNodeID == parents[u] || rightNodeID == parents[u]){
			continue;
		}

		// because each edge has a left and right node, we have to check
		// which one is different than the "parent node" to recursively
		// call the function again

		if (leftNodeID != u){
			dfsCycle(leftNodeID, u, colored, marked, parents, cycleNumber);
		}
		else if (rightNodeID != u){
			dfsCycle(rightNodeID, u, colored, marked, parents, cycleNumber);
		}

	}

	//node has ben completely visited
	colored[u] = COLORED;

}
//********************************************************************
// Method:			createCycleList
//
// Description: after all the cycles have been detected, put
//							them in a list to be accesses later. the list
//							is a vector of vectors of strings.
//
// Parameters:  marked - the array of node ids marked as in a cycle
//							cycleNumber - the total number of cycles found
//
// Returned:    the list of cycles
//
//********************************************************************
std::vector<std::vector<std::string>> GraphColoring::createCycleList
					(int marked[], int &cycleNumber){
	int numEdges = mpOriginalGraph->getAllEdges().size();
	std::vector<Node *> allNodes = mpOriginalGraph->getAllNodes();
	std::vector<std::vector<std::string>> tempCycleList(numEdges,
			std::vector<std::string>(0));

	//push the edges with marked nodes into the cycle adjacency list
	for (int i = 0; i < numEdges; i++){
		if (marked[i] != 0){
		 tempCycleList[marked[i] - 1].push_back
		 	 	 	 	 	 (mpOriginalGraph->getNode(i)->getName());
		}
	}

	mCycleList = tempCycleList;
	mCycleList.resize(cycleNumber);

	return mCycleList;
}
//********************************************************************
// Method:			printCycleList
//
// Description: print node names of each cycle found in the original
//							graph
//
// Parameters:  totalCycles - the total number of cycles found
//
// Returned:    none
//
//********************************************************************
void GraphColoring::printCycleList(){
	int totalCycles = mCycleList.size();

	for (int i = 0; i < totalCycles; i++){
		std::cout << "Cycle " << i + 1 << ": ";
		for (std::string x: mCycleList[i]){
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
}
