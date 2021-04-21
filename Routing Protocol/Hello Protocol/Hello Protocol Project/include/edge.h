//*****************************************************************************
// File name:  Edge.h
// Author:     Chadd Williams
// Date:       10/2/2013
// Class:      CS380
// Assignment: Path Finder
// Purpose:    Define an Edge in a graph
//*****************************************************************************

#pragma once
#include <string>

class Node;
class Edge
{
public:

	virtual ~Edge();
	Edge(Node* left = nullptr, Node* right = nullptr, int weight = 0);

	// an edge has two end points. allow the user to
	// retrieve the data for each end point.
	// the notion of left and right is arbitrary.

	std::string getLeftEndName() const;
	std::string getRightEndName() const;

	// each edge has a weight
	int getWeight() const;
	void setWeight(int newWeight);
	Node * getLeftNode();
	Node * getRightNode();

private:
	Node * mLeft;
	Node *mRight;
	int mWeight;
};
