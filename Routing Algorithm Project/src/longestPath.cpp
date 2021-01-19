//********************************************************************
// File name:  longestPath.cpp
// Author:     Megan DeYoung
// Date:       1/6/2021
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    driver to run the full "Longest Path" Algorithm
//********************************************************************

#include <iostream>
#include <fstream>
#include "..//include//scenicRouting.h"
using namespace std;

//********************************************************************
// Method:			main()
//
// Description: driver for the full algorithm
//
// Parameters:  none
//
// Returned:    EXIT_SUCCESS
//
//********************************************************************
int main() {
	const string INPUT_FILE = "colorpoints.txt";
	const string HEADER_LINE = "-----------------------------------";
	const string QUIT = "q";
	const int MAX_LOOP_NODES = 10000;
	int numNodes, numEdges;
	string enterNodes = "Y";
	string nodeName1;
	string nodeName2;
	std::vector<std::string> finalPath;

	Graph *pOriginalGraph = new Graph();
	Graph *pMST = new Graph();
	Kruskal *pKruskal = new Kruskal(pOriginalGraph, pMST);
	GraphColoring *pGraphColoring = new GraphColoring(pOriginalGraph);

	// read from file and insert nodes into the "original graph"
  readGraphFromFile(pOriginalGraph, INPUT_FILE, numNodes, numEdges);

  //detect all loops in the original graph to be used later
  initCycleList(pGraphColoring, numEdges, MAX_LOOP_NODES);

	//use kruskal's algorithm to create a maximum spanning tree
	initMST(pKruskal);

	//print header
	cout << HEADER_LINE << std::endl <<
			"SCENIC ROUTING: longest path finder" << std::endl
			<< HEADER_LINE << std::endl << std::endl;

	// get user input until they are finished.
	while(enterNodes != QUIT){
		cout << "Enter the name of the source node: ";
		cin >> nodeName1;
		cout << "Enter the name of the destination node: ";
		cin >> nodeName2;

		cout << endl;

		// get path between them (with error checking)
		finalPath = getPath(pMST, pOriginalGraph, nodeName1,
				nodeName2, pGraphColoring);

		printPathWithCost(finalPath, pOriginalGraph);

		cout << std::endl << std::endl
				<< "Press any key to continue OR q to QUIT ";
		cin >> enterNodes;

		cout << std::endl << std::endl;

	}


	//free memory
	delete pKruskal;
	delete pGraphColoring;

	return 0;
}


