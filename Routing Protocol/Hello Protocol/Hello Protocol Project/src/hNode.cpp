//***************************************************************************
// File name:
// Author:
// Date:
// Class:
// Assignment:
// Purpose:
//***************************************************************************

#include "..//include//hNode.h"

std::ostream& operator<<(std::ostream &os, const HNode &theNode)
{
	theNode.outputNode(os);
	return os;
}

HNode::HNode()
{
	mKey = 0;
}

bool HNode::calculateNewKey(int key)
{
	mKey = key;
	return true;
};

HNode::HNode(int key)
{
	mKey = key;
}

HNode::~HNode()
{
}

bool HNode::operator< (ComparableItem const &right) const
{
	return mKey < (dynamic_cast<const HNode*> (&right))->mKey;
}
bool HNode::operator> (ComparableItem  const &right) const
{
	return mKey > (dynamic_cast<const HNode*> (&right))->mKey;
}
bool HNode::operator== (ComparableItem const  &right)const
{
	return mKey == (dynamic_cast<const HNode*> (&right))->mKey;
}

// Function to change the key of the Node to the passed in argument
// The argument is a void* since the key of the Node is dependent upon
// the implementation

void HNode::setKey(int key)
{
	mKey = (key);
}

// Function to output the contents of the Node. This will be called
// by the function displayHeap in the class MaxHeap

void HNode::outputNode(std::ostream& os) const
{
	os << mKey;
}

bool HNode::getKey(int *pKey) const
{
	bool retVal = true;

	*pKey = mKey;
	return retVal;
}
