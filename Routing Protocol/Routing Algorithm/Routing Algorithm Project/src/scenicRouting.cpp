//*********************************************************************
// File name:  scenicRouting.cpp
// Author:     Megan DeYoung
// Date:       1/13/2021
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    implement helper functions for the scenic routing
//						 algorithm
//**********************************************************************

#include "..//include//scenicRouting.h"

//********************************************************************
// Method:			readGraphFromFile
//
// Description: read graph info from a file. the data is in the form:
//							number of nodes, each node by name, number of edges
//							each edge as a line of - node1 node2 weight
//
// Parameters:  pGraph - the graph pointer to add nodes and edges to
//
// Returned:    none
//
//********************************************************************
void readGraphFromFile(Graph *pGraph, std::string fileName,
		int &numNodes, int &numEdges){
	std::ifstream nodeFile;
	std::string name;
	int weight;
	Node *pNode, *pNodeLeft, *pNodeRight;
	nodeFile.open(fileName);

	nodeFile >> numNodes;

	for (int i = 0; i < numNodes; ++i){
		nodeFile >> name;
		pNode = new Node(name);
		pGraph->addNode(pNode);
	}

	nodeFile >> numEdges;

	for (int i = 0; i < numEdges; i++){
		nodeFile >> name;
		pNodeLeft = pGraph->getNode(name);
		if (NULL == pNodeLeft) {
			exit(-1);
		}

		nodeFile >> name;
		pNodeRight = pGraph->getNode(name);
		if (NULL == pNodeRight) {
			exit(-1);
		}

		nodeFile >> weight;
		pGraph->addEdge(pNodeLeft, pNodeRight, weight);
	}

	nodeFile.close();
}
//********************************************************************
// Method:			initCycleList
//
// Description: create the list of all the cycles in the original
//							graph to be added to paths later
//
// Parameters:  pGraphColoring - the graphColoring object
//
//
// Returned:    none
//
//********************************************************************
void initCycleList(GraphColoring *pGraphColoring, int numEdges,
		const int MAX_LOOPS){

	int u = 1;
	int p = 0;
	int cycleNumber = 0;
	int parents[numEdges];
	int marked[MAX_LOOPS];
	int colored[MAX_LOOPS];

	//initialize arrays
	for (int i = 0; i < MAX_LOOPS; i++){
		if (i < numEdges){
			parents[i] = i;
		}
		marked[i] = 0;
		colored[i] = 0;
	}

	pGraphColoring->dfsCycle(u, p, colored, marked,
			parents, cycleNumber);

	pGraphColoring->createCycleList(marked, cycleNumber);
}
//********************************************************************
// Method:			initMST
//
// Description: create a maximum spanning tree from the original
//							graph
//
// Parameters:  pGraphColoring - the graphColoring object
//
//
// Returned:    none
//
//********************************************************************
void initMST(Kruskal *pKruskal){
	pKruskal->useKruskal();
}
//********************************************************************
// Method:			getPath
//
// Description: using bfs, get the path between two nodes, adding a
// 							loop if the nodes are already adjacent to each other
//
// Parameters:  srcNodeName - name of the source node
//							destNodeName - name of the destination node
//							pMST - the max spanning tree for finding the
//										 path
//							pOriginalGraph - original graph to find the loops
//							pGP - the coloring graph object used to get the
//										list of cycles
//
//
// Returned:    the name of the nodes in the path as a vector
//
//********************************************************************
std::vector<std::string> getPath(Graph *pMST, Graph *pOriginalGraph,
		std::string srcNodeName, std::string destNodeName,
		GraphColoring *pGP){

	Node * srcNode = pMST->getNode(srcNodeName);
	Node * destNode = pMST->getNode(destNodeName);
	int srcNodeID;
	int destNodeID;
	unsigned int displace = 1;
	std::string currentNode = srcNodeName;
	std::string tempName;
	std::vector<std::string> visitedLoopNodes;
	std::vector<std::string> pathNames;
	std::vector<std::string> loopNodes;
	std::map<std::string, std::vector<Edge *>> adjList =
			pOriginalGraph->getList();
	std::vector<Edge *> edgeList;

	if (NULL != srcNode && NULL != destNode){
		srcNodeID = srcNode->getNodeID();
		destNodeID = destNode->getNodeID();

		pathNames = pMST->breadthFirstSearch(srcNodeID, destNodeID);

		// if path nodes are adjacent or the same node add a loop
		if (pathNames.size() <= 2){
			loopNodes = getLoop(srcNodeName, destNodeName, pGP);

			visitedLoopNodes.push_back(currentNode);

			while (displace <= loopNodes.size()){
				pathNames.insert(pathNames.begin() + 1, currentNode);
				edgeList = adjList[currentNode];

				//find next node to look at through adjacency list
				for(Edge * currentEdge : edgeList){

					// get adjacent node name
					if (currentEdge->getLeftEndName() != currentNode){
						tempName = currentEdge->getLeftEndName();

					}
					else if (currentEdge->getRightEndName() != currentNode){
						tempName = currentEdge->getRightEndName();

					}

					// check to see if the node is in the loop and not already
					// visited
					if (std::find(loopNodes.begin(), loopNodes.end(), tempName)
						!= loopNodes.end() && std::find(visitedLoopNodes.begin(),
								visitedLoopNodes.end(), tempName) ==
										visitedLoopNodes.end()){

						visitedLoopNodes.push_back(tempName);
						break;

					}

				}
				currentNode = tempName;
				displace++;
			}

		}

	}

	else {
		std::cout << "Invalid Node Found."
				" Here are the following nodes you can choose from:"
				<< std::endl;
		pMST->printNodes();
	}


	return pathNames;
}
//********************************************************************
// Method:			getLoop
//
// Description: get any existing loops from the source node that
//							doesn't include the destination
//
// Parameters:  srcNodeName - name of the source node
//							destNodeName - name of the destination node
//							pGraphColoring - object containing cycle list
//
// Returned:    the name of the nodes in the loop as a vector
//
//********************************************************************
std::vector<std::string> getLoop(std::string srcNodeName,
			std::string destNodeName, GraphColoring *pGraphColoring){
	std::vector<std::string> loopPath;

	std::vector<std::vector<std::string>> cycleList
					= pGraphColoring->getCycleList();

	for(std::vector<std::string> loop : cycleList){
		// if a loop is found that includes the src but not the dest
		// unless they are the same
		if (std::find(loop.begin(), loop.end(), srcNodeName)
			!= loop.end() && (std::find(loop.begin(), loop.end(),
					destNodeName) == loop.end() || srcNodeName == destNodeName))
					{

						for (std::string nodeName : loop){
							loopPath.push_back(nodeName);
						}
						break;
					}
	}


	return loopPath;
}
//********************************************************************
// Method:			printPathWithCost
//
// Description: print the final loop including edge weights and final
//							cost
//
// Parameters:  path - list of node names of the path
//							pOriginalGraph - graph to get correct edge weights
//															 from including loop edges that
//															 would not be in the MST
//
// Returned:    the name of the nodes in the loop as a vector
//
//********************************************************************
void printPathWithCost(std::vector<std::string> path,
		Graph *pOriginalGraph){

	std::map<std::string, std::vector<Edge *>> adjList =
			pOriginalGraph->getList();
	std::string leftName, rightName;
	int totalCost = 0;

	for (unsigned int i = 0; i < path.size() - 1; i++){
		leftName = path[i];
		rightName = path[i + 1];
		std::cout << leftName << " -> " << rightName;

		for(Edge * currentEdge : adjList[path[i]]){
			if (currentEdge->getLeftEndName() == rightName ||
					currentEdge->getRightEndName() == rightName){
				totalCost += currentEdge->getWeight();
				std::cout << "  Cost: " << currentEdge->getWeight() << std::endl;
				break;
			}
		}

	}
	std::cout << std::endl << "TOTAL COST: " <<  totalCost << std::endl;
}


