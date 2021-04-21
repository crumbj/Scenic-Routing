//*****************************************************************************
// File name:  helloMulticast.h
// Author:     Megan DeYoung
// Date:       3/16/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    define functions to be able to send and receive hello packets
//*****************************************************************************
#include "helloPacket.h"

#ifndef HELLO_H_
#define HELLO_H_

static const int SEND_INTERVAL = 15;


extern void sendHelloMulticast (std::string routerIP);
extern ScenicHelloPtr recvHelloMulticast (char * routerIP);
extern ScenicHelloPtr recvACK (char * routerIP);

// for use with threads
extern void * sendHelloLoop (void * routerIP);

extern void * recvHelloLoop (void * routerIP);

extern void * recvACKLoop (void * routerIP);

// function to use a mutex with the global time vector
extern void updateTimeSinceACK (long int timeACK);



#endif /* HELLO_H_ */
