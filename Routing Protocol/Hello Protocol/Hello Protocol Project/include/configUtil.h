//*****************************************************************************
// File name:  configUtil.h
// Author:     Megan DeYoung
// Date:       3/16/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    define helper functions to help configure a router
//*****************************************************************************

#pragma once
#include <string>
#include <cstring>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netdb.h>

#include <fstream>
#include <iostream>

#include "graph.h"
#include "node.h"

#ifndef CONFIGUTIL_H_
#define CONFIGUTIL_H_

extern std::string getRouterIP ();
extern std::string getIPFromUnsignedInt (unsigned int ip);
extern void readConfigFile (Graph *pcTheGraph);
extern std::vector<Node *> getNeighbors (Graph *pcTheGraph,
		std::string routerIP);



#endif /* CONFIGUTIL_H_ */
