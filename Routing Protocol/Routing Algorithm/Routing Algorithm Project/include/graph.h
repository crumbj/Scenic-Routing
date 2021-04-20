//*****************************************************************************
// File name:  Graph.h
// Author:     Chadd Williams edited by Megan DeYoung
// Date:       10/2/2013 edited 1/5/2020
// Class:      CS380
// Assignment: Path Finder
// Purpose:    define graph class
//*****************************************************************************

#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <list>
#include <map>
#include "node.h"

class Graph {
public:
	Graph();
	~Graph();
	void addNode(Node *pNode);
	Node * getNode(std::string name);
	Node * getNode(int id);
	void addEdge(Node *pLeft, Node *pRight, int weight);
	std::vector<Node *> getAllNodes();
	std::vector<Edge *> &getAllEdges(){return mAllEdges;};
	int getEdgeWeight(std::string nodeName, std::string searchName);
	std::map <std::string, std::vector<Edge *>> getList();
	int getNumNodes(){return getAllNodes().size();};
	int getNumEdges(){return getAllEdges().size();};
	std::vector<std::string> breadthFirstSearch(int srcID, int destID);
	void printList();
	void printNodes();


private:
	std::vector<Node *> mNodes;
	std::vector<Edge *> mAllEdges;
	std::map <std::string, std::vector<Edge *>> adjacencyList;
};
