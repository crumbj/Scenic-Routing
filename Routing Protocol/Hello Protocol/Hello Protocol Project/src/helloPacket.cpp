//*****************************************************************************
// File name:  helloPacket.h
// Author:     Megan DeYoung
// Date:       3/16/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    define helper functions to help configure a router
//*****************************************************************************

#include "../include/helloPacket.h"

void constructPacket (ScenicHelloPtr pPacket, char * pszSrcAddress,
		char *pszDestAddress, char helloType)
{
	struct timeval time;
	long int seconds, useconds, milliseconds;
	char timeString[256];

	pPacket->type = helloType;
	// srcAddress
	memset(pPacket->srcAddress, '\0', ADDR_LEN);
	strncpy (pPacket->srcAddress, pszSrcAddress, ADDR_LEN);

	// destAddress
	memset(pPacket->destAddress, '\0', ADDR_LEN);
	strncpy (pPacket->destAddress, pszDestAddress, ADDR_LEN);

	// convert time to string and copy
	gettimeofday(&time, NULL);
	seconds = time.tv_sec;
	useconds = time.tv_usec;
	milliseconds = ((seconds) * 1000 + useconds/1000.0);
	sprintf (timeString, "%ld", milliseconds);
	memset(pPacket->timeSent, '\0', 256);
	strncpy(pPacket->timeSent, timeString, 256);

}

char * getTimeSent (ScenicHelloPtr pPacket)
{
	return pPacket->timeSent;
}

char * getSrcAddress (ScenicHelloPtr pPacket)
{
	return pPacket->srcAddress;
}


char * getDestAddress (ScenicHelloPtr pPacket)
{
	return pPacket->destAddress;
}

char * getMessage (ScenicHelloPtr pPacket)
{
	char *pszMessage = new char[286];
	// a message in the form "hello from -src dest(15)- at -TimeSent(256)
	memset(pszMessage, '\0', 286);
	strncat(pszMessage, "hello from ", 11);
	strncat(pszMessage, pPacket->srcAddress, ADDR_LEN);
	strncat(pszMessage, " at ", 4);
	strncat(pszMessage, pPacket->timeSent, 256);

	return pszMessage;
}



