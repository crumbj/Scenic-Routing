//*****************************************************************************
// File name:  helloPacket.h
// Author:     Megan DeYoung
// Date:       3/16/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    define helper functions to help configure a router
//*****************************************************************************

#ifndef HELLOPACKET_H_
#define HELLOPACKET_H_

#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static const int ADDR_LEN = 15;
static const char HELLO_ACK = 'A';
static const char HELLO_SEND = 'R';

typedef struct ScenicHello *ScenicHelloPtr;
typedef struct ScenicHello
{
	char type;
	char srcAddress[15];
	char destAddress [15];
	char timeSent[256];

} ScenicHello;

extern void constructPacket (ScenicHelloPtr pPacket, char * pszSrcAddress,
		char *pszDestAddress, char helloType);

extern char * getTimeSent (ScenicHelloPtr pPacket);

extern char * getSrcAddress (ScenicHelloPtr pPacket);

extern char * getMessage (ScenicHelloPtr pPacket);

extern char * getDestAddress (ScenicHelloPtr pPacket);



#endif /* HELLOPACKET_H_ */
