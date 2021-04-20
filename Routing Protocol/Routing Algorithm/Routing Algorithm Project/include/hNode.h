//***************************************************************************
// File name:		HNode.h
// Author:			Shereen Khoja
// Author:			Chadd Williams
// Date:				02/16/2011
// Edited:			09/12/2013
// Class:				CS380
// Assignment:	Disk Scheduling
// Purpose:			This is the header file for the abstract Node class.
//***************************************************************************

#pragma once

#include <iostream>
#include "ComparableItem.h"

class HNode : public ComparableItem
{
public:
	// ComparableItem interface
	virtual bool operator< (ComparableItem const &right) const;
	virtual bool operator> (ComparableItem  const &right) const;
	virtual bool operator== (ComparableItem const  &right)const;

	// Function to change the key of the HNode to the passed in argument

	virtual void setKey(int);

private:
	// Function to output the contents of the HNode. This will be called
	// by the operator<<
	virtual void outputNode(std::ostream& os) const;

	int mKey;

public:
	HNode();
	HNode(int key);
	virtual ~HNode();

	// Function to get the current key.
	virtual bool getKey(int*) const;

	// This method allows the key to be changed based upon some
	// other data.  Each subclass must implement this method.
	// this might calculate a new key and then call changeKey.
	// return true on success or false on error
	// errors include incorrect or incorrectly sized data
	// being sent to the function
	virtual bool calculateNewKey(int);

	friend std::ostream& operator<<(std::ostream &os, const HNode &theNode);
};
