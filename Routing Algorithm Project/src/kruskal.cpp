//*****************************************************************************
// File name:  kruskal.cpp
// Author:     Megan DeYoung
// Date:       11/19/2020
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    Implement Kruskal's Algorithm to create MST
//*****************************************************************************

#include "..//include//kruskal.h"

//********************************************************************
// Method:			Kruskal
//
// Description: initialize member variables (constructor)
//
// Parameters:  graph - the graph to run the algorithm on, which
//											has been initialized with nodes, edges, and
//											map
//							MST - the graph has been initialized with nodes
//
// Returned:    none
//
//********************************************************************
Kruskal::Kruskal(Graph* graph, Graph *MST) {
	mpOriginalGraph = graph;
	mpMST = MST;
}
//********************************************************************
// Method:			~Kruskal
//
// Description: destructor
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
Kruskal::~Kruskal() {
	delete mpOriginalGraph;
	delete mpMST;
}
//********************************************************************
// Method:			negateAllWeights
//
// Description: negate all the edge weights in the original graph
//
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
void Kruskal::negateAllWeights() {
	std::vector<Edge *> edgeList = mpOriginalGraph->getAllEdges();
	int currentWeight;

	//negate edge weights
	for (Edge * currentEdge: edgeList){
		currentWeight = currentEdge->getWeight();
		currentWeight *= -1;
		currentEdge->setWeight(currentWeight);
	}
}
//********************************************************************
// Method:			useKruskal
//
// Description: apply Kruskal's algorithm to the original graph to
//							maximum spanning tree
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
void Kruskal::useKruskal() {
	//negate all graph weights in original graph to make
	// MST a maximum spanning tree by adding edges.

	negateAllWeights();
	sortEdgesLowToHigh(mpOriginalGraph->getAllEdges());

	//initialize parent array
	//size of array is num of nodes
	int numOfNodes = mpOriginalGraph->getNumNodes();

	int parentList [numOfNodes];
	for (int i = 0; i < numOfNodes; i++){
			parentList[i] = i;
	}

	Node * leftNode;
	Node * rightNode;
	Node * leftEdgeNode;
	Node * rightEdgeNode;
	Node * pNewLeft;
	Node * pNewRight;
	Node * tempLeft;
	Node * tempRight;
	std::vector<Edge *> originalEdges = mpOriginalGraph->getAllEdges();
	std::vector<std::string> addedNodes;

	int uRep, vRep;
	int length = originalEdges.size();

	for(int i = 0; i < length; i++){
		leftNode = originalEdges.at(i)->getLeftNode();
		rightNode = originalEdges.at(i)->getRightNode();

		uRep = findSet(leftNode->getNodeID(), parentList);
		vRep = findSet(rightNode->getNodeID(), parentList);
		if (uRep != vRep){
			leftEdgeNode = mpOriginalGraph->getNode(leftNode->getNodeID());
			rightEdgeNode = mpOriginalGraph->getNode(rightNode->getNodeID());

			// if left node has not already been added
			if (std::find(addedNodes.begin(), addedNodes.end(),
					leftEdgeNode->getName()) == addedNodes.end()){
				addedNodes.push_back(leftEdgeNode->getName());
				pNewLeft = new Node(leftEdgeNode->getName());
				mpMST->addNode(pNewLeft);
			}
			// if right node has not already been added
			if (std::find(addedNodes.begin(), addedNodes.end(),
								rightEdgeNode->getName()) == addedNodes.end()){
					addedNodes.push_back(rightEdgeNode->getName());
					pNewRight = new Node(rightEdgeNode->getName());
					mpMST->addNode(pNewRight);
			}

			//either use existing node for edge, or new node
				tempRight = mpMST->getNode(rightEdgeNode->getName());
				tempLeft = mpMST->getNode(leftEdgeNode->getName());

			//add edge to graph
			mpMST->addEdge(tempLeft, tempRight,
					originalEdges.at(i)->getWeight());

			makeUnion(uRep, vRep, parentList);

		}
	}
	// return original graph to its original edge weights
	negateAllWeights();
	/*std::cout << "ORIGINAL NODES" << std::endl;
	mpOriginalGraph->printNodes();
	std::cout << std::endl << "MST NODES" << std::endl;*/
	//mpMST->printList();

}
//********************************************************************
// Method:			findSet
//
// Description: divides the nodes into clusters recursively and allows
//							us to check if a node is in the same cluster as
//							another (which would be creating a cycle) and
//							decide to exclude it from the spanning tree
//              PART OF THE UNION FIND ALGORITHM
//
// Parameters:  i - node id to check if in the cluster
//							parentList - the list of parents
//
// Returned:    i, if i is the parent of itself, else call recursively
//
//********************************************************************
int Kruskal::findSet(int i, int *parentList){
	if (i == parentList[i]) {
		return i;
	}
	else {
		return findSet(parentList[i], parentList);
	}
}
//********************************************************************
// Method:			unionSet
//
// Description: if the two nodes are in the same cluster, make a union
//							of their sets and replace their original set to be the
//              new union
//							PART OF THE UNION FIND ALGORITHM
//
// Parameters:  u - node 1 id
//							v - node 2 id
//
// Returned:    none
//
//********************************************************************
void Kruskal::makeUnion(int u, int v, int *parentList){
	parentList[u] = parentList[v];
}

//********************************************************************
// Method:			sortEdgesLowtoHigh
//
// Description: sort MST edges from low to high using insertion sort
//
// Parameters:  edgeList - list of edges passed by reference to
//													be sorted in ascending order
//
// Returned:    none
//
//********************************************************************
void Kruskal::sortEdgesLowToHigh(std::vector<Edge *> &edgeList){
	int j, currentWeight;
	int size = edgeList.size();
	Edge * currentEdge;

	for (int i = 1; i < size; i++){
		currentWeight = edgeList.at(i)->getWeight();
		currentEdge = edgeList.at(i);
		j = i - 1;

		while(j >= 0 && edgeList.at(j)->getWeight() > currentWeight){
			edgeList.at(j + 1) = edgeList.at(j);
			j = j - 1;
		}
		edgeList.at(j + 1) = currentEdge;
	}
}

//********************************************************************
// Method:			printMSTAdjList
//
// Description: print the adjacency list of the max spanning tree. all
//							the edge weights should be negative
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
void Kruskal::printMSTAdjList(){
	mpMST->printList();
}
//********************************************************************
// Method:			printEdges
//
// Description: print only the edges with end names and weights
//
// Parameters:  pEdgeList - the edge list to be printed
//
// Returned:    none
//
//********************************************************************
void Kruskal::printEdges(std::vector<Edge *> pEdgeList) {
	for (Edge * currentEdge: pEdgeList){
		std::cout << "\t" << currentEdge->getLeftEndName() << " " <<
							currentEdge->getRightEndName() << "  "
							<< currentEdge->getWeight()
							<< std::endl;
	}
}
