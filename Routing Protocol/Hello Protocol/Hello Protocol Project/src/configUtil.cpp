//*****************************************************************************
// File name:  configUtil.cpp
// Author:     Megan DeYoung
// Date:       3/16/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    implement helper functions that configure a router
//*****************************************************************************

#include "..//include//configUtil.h"

//********************************************************************
// Method:			getRouterIP
//
// Description: get the ip address from the router the program is
//							running on
//
// Parameters:  None
//
// Returned:    the machine's IPv4 ip address as a string
//
//********************************************************************'
std::string getRouterIP ()
{
	const char *THIS_INTERFACE = "eth0";
		struct ifaddrs *ifaddr, *ifa;
		int family, s;
		char host[NI_MAXHOST];
		std::string thisIP;

		if (getifaddrs(&ifaddr) == -1)
		{
		        perror("getifaddrs");
		        exit(EXIT_FAILURE);
		}
		for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
		{
		  family = ifa->ifa_addr->sa_family;

		  if (family == AF_INET)
		  {
		     s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
		                     host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		     if (s != 0)
		      {
		         printf("getnameinfo() failed: %s\n", gai_strerror(s));
		         exit(EXIT_FAILURE);
		      }

		     if (strcmp(ifa->ifa_name,THIS_INTERFACE) == 0)
		     {
		    	 thisIP = host;
		    	 break;
		     }
		      //printf("<Interface>: %s \t <Address> %s\n",
		      // ifa->ifa_name, host);
		   }
		 }

		free (ifaddr);
		return thisIP;
}
//********************************************************************
// Method:			getIPFromUnsignedInt
//
// Description: get the IPv4 ip address from an unsigned int to a
//							string format
//
// Parameters:  ip - the ip address that had was converted to
//											an unsigned int using inet_pton
//
// Returned:    the ip address in string format
//
//********************************************************************
std::string getIPFromUnsignedInt (unsigned int ip)
{
	char ipAsString[15];
	unsigned char bytes[4];
	    bytes[0] = ip & 0xFF;
	    bytes[1] = (ip >> 8) & 0xFF;
	    bytes[2] = (ip >> 16) & 0xFF;
	    bytes[3] = (ip >> 24) & 0xFF;
	    sprintf(ipAsString,"%d.%d.%d.%d", bytes[0],
	    		bytes[1], bytes[2], bytes[3]);


	return ipAsString;
}
//********************************************************************
// Method:			readConfigFile
//
// Description: read from the configuration file to set up the
//							initial graph of neighbors
//
// Parameters:  pcTheGraph - the graph to initialize
//
// Returned:    None
//
//********************************************************************'
void readConfigFile (Graph *pcTheGraph)
{
		const std::string INPUT_FILE = "/tmp/routerConfig.txt";
		const int INIT_WEIGHT = 1;
		std::ifstream configFile;
		std::string nodeName;
		std::string nodeIP;
		unsigned int nodeIdIp;
		int numRouters;
		int numEdges;
		Node *pNode, *pNodeLeft, *pNodeRight;

		// read configuration file (use inet_pton to store address as int)
		configFile.open (INPUT_FILE);
		configFile >> numRouters;
		for (int i = 0; i < numRouters; i++)
		{
			configFile >> nodeName;
			configFile >> nodeIP;

			pNode = new Node(nodeName);
			inet_pton (AF_INET, nodeIP.c_str(), &nodeIdIp);

			// add node automatically sets the node id to the number nodes
			// currently in the graph, so you must assign the ip address
			// as the id after its added to the list
			pcTheGraph->addNode (pNode);
			pNode->setNodeID (nodeIdIp);

		}

		configFile >> numEdges;
		for (int j = 0; j < numEdges; j++)
		{
			configFile >> nodeIP;
			inet_pton (AF_INET, nodeIP.c_str(), &nodeIdIp);

			pNodeLeft = pcTheGraph->getNode(nodeIdIp);

			configFile >> nodeIP;
			inet_pton (AF_INET, nodeIP.c_str(), &nodeIdIp);

			pNodeRight = pcTheGraph->getNode(nodeIdIp);

			pcTheGraph->addEdge(pNodeLeft, pNodeRight, INIT_WEIGHT);

		}
		
		configFile.close();

}
//********************************************************************
// Method:			getNeighbors
//
// Description: get a list of this router's neighbor nodes.
//
// Parameters:  pcTheGraph - the graph to initialize
//
// Returned:    None
//
//********************************************************************'
std::vector<Node *> getNeighbors (Graph *pcTheGraph,
		std::string routerIP)
{
	Node *pNeighbor;
	unsigned int convertIP;
	std::string homeNodeName;
	std::map <std::string, std::vector<Edge *>> adjList;
	std::vector<Node *> allNeighbors;

	// get name of node with our ip addr
	adjList = pcTheGraph->getList();
	inet_pton(AF_INET, routerIP.c_str(), &convertIP);
	homeNodeName = pcTheGraph->getNode(convertIP)->getName();

	// get neighbors from list using this name
	std::vector<Edge *> myNeighborEdges = adjList[homeNodeName];

	for (Edge * edge : myNeighborEdges)
	{
		if (edge->getLeftEndName() != homeNodeName)
		{
			pNeighbor = edge->getLeftNode();
		}
		else
		{
			pNeighbor = edge->getRightNode();
		}

		allNeighbors.push_back(pNeighbor);

	}

	return allNeighbors;
}




