//*****************************************************************************
// File name:  Node.h
// Author:     Chadd Williams (mod Chris Lane, mod Megan DeYoung)
// Date:       10/2/2013 (3/27/2019)
// Class:      CS380
// Assignment: Path Finder
// Purpose:    Define a node in a graph
//*****************************************************************************

#pragma once
#include <string>
#include <vector>
#include "hNode.h"
#include "edge.h"

class Edge;
class Node : HNode
{
public:
	// Each node must have a name
	Node(std::string name) : mName(name) {};

	// virtual destructor
	virtual ~Node() {};

	// get the name
	std::string getName() const { return mName; };

	void setNodeID(int id) { mNodeID = id; };

	int getNodeID() const { return mNodeID; };

	virtual void setKey(int newKey) { HNode::setKey(newKey); };

	void setParent(Node *newParent) { mParent = newParent; };

	std::string getParent() { return mParent->getName(); };

	virtual bool getKey(int* theKey) const { return HNode::getKey(theKey); };

	virtual bool calculateNewKey(int newKey)
	{ return HNode::calculateNewKey(newKey); };

private:
	std::string mName;
	Node * mParent;
	int mNodeID;
};
