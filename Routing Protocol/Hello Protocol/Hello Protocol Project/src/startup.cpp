//*********************************************************************
// File name:  startup.cpp
// Author:     Megan DeYoung
// Date:       4/19/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    upon the start of the program, run the hello protocol
//*********************************************************************

#include "../include/graph.h"
#include "../include/configUtil.h"
#include "../include/helloMulticast.h"
#include <string.h>
#include <signal.h>
#include <thread>
using namespace std;

std::map<std::string, long int> timeSinceACK;

int main(int argc, char *argv[])
{
	Graph *pcGraph = new Graph();
	std::vector<Node *> routerNeighbors;
	std::string routerIP;
	std::string neighborIP;
	std::string tempIP;
	routerIP = argv[1];

	// read the config file and get this router's neighbors
	readConfigFile (pcGraph);
	
	routerNeighbors = getNeighbors(pcGraph, routerIP);

	std::cout << "\ndone reading in graph...\n";

	// receive packets from the multicast address
	std::thread recvHelloThread(recvHelloLoop, (void *)routerIP.c_str());
	// send packet every 15 seconds to multicast address
	std::thread sendHelloThread(sendHelloLoop, (void *)routerIP.c_str());

	// receive packets not from the mulitcast address
	std::thread recvACKThread(recvACKLoop, (void *)routerIP.c_str());

	sendHelloThread.join();
	recvHelloThread.join();
	recvACKThread.join();


	// if don't receive an ack after a certain amount of time, update graph.


	delete (pcGraph);
	return 0;
}


