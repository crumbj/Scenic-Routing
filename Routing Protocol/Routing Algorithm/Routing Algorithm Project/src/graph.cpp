//*****************************************************************************
// File name:  Graph.cpp
// Author:     Megan DeYoung
// Date:       4/13/2019
// Class:      CS380
// Assignment: Path Finder
// Purpose:    implement graph class functions
//*****************************************************************************

#include "..//include//graph.h"

//********************************************************************
// Method:			Graph
//
// Description: initialize member variables (constructor)
//
// Parameters:  none
//
// Returned:    none
//	
//********************************************************************
Graph::Graph() {
}
//********************************************************************
// Method:			~Graph
//
// Description: destructor
//
// Parameters:  none
//
// Returned:    none
//	
//********************************************************************
Graph::~Graph() {

	for (Edge * e : mAllEdges) {
		delete e;
	}
	for (Node * n : mNodes) {
		delete n;
	}

}
//********************************************************************
// Method:			addNode
//
// Description: add a node to the graph
//
// Parameters:  pNode - the node to add to the graph
//
// Returned:    none
//	
//********************************************************************'
void Graph::addNode(Node *pNode) {
	std::vector<Edge *> mTemp;
	pNode->setNodeID((int)mNodes.size());
	mNodes.push_back(pNode);
	adjacencyList.insert(make_pair(pNode->getName(), mTemp));
}
//********************************************************************
// Method:			getNode
//
// Description: get a pointer to a node in the graph
//
// Parameters:  string - name of new to get
//
// Returned:    pointer to the node
//	
//********************************************************************
Node* Graph::getNode(std::string name) {
	unsigned int i = 0;
	bool bNodeFound = false;

	while (!bNodeFound && i < mNodes.size()) {
		if (mNodes[i]->getName() == name) {
			return mNodes[i];
		}

		i++;
	}

	return NULL;
}
//********************************************************************
// Method:			addEdge
//
// Description: add an edge to the correct nodes
//
// Parameters:  pLeft - pointer to the left side of the edge
//							pRight - pointer to the right side of the edge
//							weight - weight of the edge
//
// Returned:    none
//	
//********************************************************************
void Graph::addEdge(Node *pLeft, Node *pRight, int weight) {  

	Edge* pEdge = new Edge(pLeft, pRight, weight);
	Node *pAddTo = getNode(pLeft->getName());
	mAllEdges.push_back(pEdge);
	adjacencyList[pAddTo->getName()].push_back(pEdge);

	pAddTo = getNode(pRight->getName());
	adjacencyList[pAddTo->getName()].push_back(pEdge);

}
//********************************************************************
// Method:			getAllNodes
//
// Description: get all the nodes in the graph
//
// Parameters:  none
//
// Returned:    vector containing the graphs nodes
//	
//********************************************************************
std::vector<Node *> Graph::getAllNodes() {
	return mNodes;
}
//********************************************************************
// Method:			getEdgeWeight
//
// Description: find edge in adjacency matrix and return weight
//
// Parameters:  none
//
// Returned:    weight of the correct edge
//	
//********************************************************************
int Graph::getEdgeWeight(std::string nodeName, std::string searchName) {

	std::vector<Edge *> theEdges = adjacencyList[nodeName];

	for (Edge * e : theEdges) {
		if (e->getRightEndName() == searchName) {
			return e->getWeight();
		}
		else if (e->getLeftEndName() == searchName) {
			return e->getWeight();
		}
	}

	return -1;

}
//********************************************************************
// Method:			getList
//
// Description: get adjacency list
//
// Parameters:  none
//
// Returned:    the adjacency list
//	
//********************************************************************
std::map<std::string, std::vector<Edge*>> Graph::getList() {
	return adjacencyList;
}
//********************************************************************
// Method:			getNode
//
// Description: get a pointer to a node in the graph
//
// Parameters:  id - id # of node to get
//
// Returned:    pointer to the node
//	
//********************************************************************
Node* Graph::getNode(int id) {
	unsigned int i = 0;
	bool bNodeFound = false;

	while (!bNodeFound && i < mNodes.size()) {
		if (mNodes[i]->getNodeID() == id) {
			return mNodes[i];
		}

		i++;
	}

	return NULL;
}

//********************************************************************
// Method:			printList
//
// Description: print the adjacency list of the graph
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
void Graph::printList(){
	std::map <std::string, std::vector<Edge *>> adjList = getList();
	std::map<std::string, std::vector<Edge *>>::iterator it;

	for (it = adjList.begin(); it != adjList.end(); it++){
		std::cout << it->first << std::endl << "Adjacent Edges for "
				<< it->first << std::endl;

		// print each edge in the list for the current node
		for (Edge * edge: it->second){
			std::cout << "\t" << edge->getLeftEndName() << " " <<
					edge->getRightEndName() << "  " << edge->getWeight()
					<< std::endl;
		}
	}

}
//********************************************************************
// Method:			printNodes
//
// Description: print the names and ids of all the nodes in the graph
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
void Graph::printNodes(){
	std::vector<Node *> allNodes = getAllNodes();

	for (Node * currentNode: allNodes){
		//std::cout << "name: " << currentNode->getName() << "  id: "
				//<< currentNode->getNodeID() << std::endl;
		std::cout << currentNode->getName() << " ";
	}
	std::cout << std::endl;
}
//********************************************************************
// Method:			breadthFirstSearch
//
// Description: find the path from one node to another
//
// Parameters:  srcID - the node id number for the source node
//							destID - the node id number for the destination node
//
// Returned:    a list of node ids (the path from src to dest)
//
//********************************************************************
std::vector<std::string> Graph::breadthFirstSearch(int srcID, int destID){
		std::list<int> idQueue;
		std::vector<std::string> path;
		int numNodes = getNumNodes();
		int currentID;
		int adjacentID;
		std::string currentName;
		Node * currentNode;

		//keep track of previous node in form
		//(index = nodeID, value = previous nodeID)
		int previous[numNodes];
		for (int i = 0; i < numNodes; i++){
					previous[i] = -1;
		}

		// mark all nodes as unvisited
		bool visited[numNodes];
		for (int i = 0; i < numNodes; i++){
			visited[i] = false;
		}

		//mark source node as visited and add to queue
		visited[srcID] = true;
		adjacentID = srcID;
		currentID = srcID;
		idQueue.push_back(srcID);

		while (!idQueue.empty() && currentID != destID){
			// dequeue a node from the queue and print it
			currentID = idQueue.front();
			idQueue.pop_front();


			//get all adjacent nodes of the current node
			//if a node has not been visited, mark it as
			//visited and add to the queue
			//adjacency list in form map<node name, list of adjacent edges>
			currentName = getNode(currentID)->getName();

			for (Edge * edge : adjacencyList[currentName]){

				// if the left node is the adjacent node
				if (edge->getLeftEndName() != currentName){
					currentNode = edge->getLeftNode();
				}
				// if the right node is the adjacent node
				else if (edge->getRightEndName() != currentName){
					currentNode = edge->getRightNode();
				}

				adjacentID = currentNode->getNodeID();
				//check if visited, update previous id array
				if (!visited[adjacentID]){
					visited[adjacentID] = true;
					previous[adjacentID] = currentID;
					idQueue.push_back(adjacentID);
				}
			}
		}

		int currentPathNodeID = destID;

		while (currentPathNodeID != -1){
			path.insert(path.begin(), getNode(currentPathNodeID)->getName());
			currentPathNodeID = previous[currentPathNodeID];
		}

		return path;
}

