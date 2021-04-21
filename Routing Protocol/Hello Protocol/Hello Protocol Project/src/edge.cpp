//*****************************************************************************
// File name:  Edge.cpp
// Author:     Megan DeYoung
// Date:       4/13/2019
// Class:      Capstone
// Assignment: Scenic Routing
// Purpose:    Define an Edge in a graph
//*****************************************************************************

#include "..//include//edge.h"
#include "..//include//node.h"

//********************************************************************
// Method:			Edge
//
// Description: initialize member variables (constructor)
//
// Parameters:  string left  - name of left point on edge
//							string right - name of right point on edge
//							weight       - the weight of the edge
//
// Returned:    none
//
//********************************************************************
Edge::Edge(Node *left, Node *right, int weight) {

	mLeft = left;
	mRight = right;
	mWeight = weight;
}
//********************************************************************
// Method:			~Edge
//
// Description: destructor
//
// Parameters:  none
//
// Returned:    none
//
//********************************************************************
Edge::~Edge() {

}
//********************************************************************
// Method:			getLeftEndName
//
// Description: get the left point of the edge
//
// Parameters:  none
//
// Returned:    string - the name of the left point of the edge
//
//********************************************************************
std::string Edge::getLeftEndName() const {
	return mLeft->getName();
}
//********************************************************************
// Method:			getRightEndName
//
// Description: get the right point of the edge
//
// Parameters:  none
//
// Returned:    string - the name of the right point of the edge
//
//********************************************************************
std::string Edge::getRightEndName() const {
	return mRight->getName();
}
//********************************************************************
// Method:			getWeight
//
// Description: get the weight of the edge
//
// Parameters:  none
//
// Returned:    int - the edge's weight
//
//********************************************************************
int Edge::getWeight() const {
	return mWeight;
}
//********************************************************************
// Method:			setWeight
//
// Description: set the weight of the edge
//
// Parameters:  none
//
// Returned:    newWeight - new weight for the edge
//
//********************************************************************
void Edge::setWeight(int newWeight) {
	mWeight = newWeight;
}

Node * Edge::getLeftNode (){
	return mLeft;
}

Node * Edge::getRightNode (){
	return mRight;
}
