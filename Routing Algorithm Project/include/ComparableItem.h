//*****************************************************************************
// File name:  ComparableItem.h
// Author:     Chadd Williams
// Date:       7/5/2013
// Class:      CS380
// Assignment: Basic Sorting
// Purpose:    To define the header file for an item that supports
//						 the Comparable interface.
//*****************************************************************************

#ifndef _ComparableItem_H_
#define _ComparableItem_H_

class ComparableItem
{
public:

	// subclass this class to allow pointers to that subclass to be
	// stored in a SortableContainer.

	// a virtual destructor to allow subclasses the ability to 
	// deallocate memory.
	virtual ~ComparableItem() {};

	// comparison methods.
	virtual bool operator< (ComparableItem const &right) const = 0;
	virtual bool operator> (ComparableItem  const &right) const = 0;
	virtual bool operator== (ComparableItem const  &right)const = 0;

};
#endif