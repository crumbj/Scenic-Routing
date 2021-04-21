//*****************************************************************************
// File name:  helloMulticast.cpp
// Author:     Megan DeYoung
// Date:       3/26/2021
// Class:      Senior Capstone
// Assignment: Scenic Routing
// Purpose:    implement the functions to be able to send and receive hello
//						 packets by mulitcasting ip datagrams
//*****************************************************************************

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
#include "../include/helloMulticast.h"


//********************************************************************
// Method:			sendHelloMulticast
//
// Description: sends a single hello packet to the multicast address
//
// Parameters:  routerP - the router IP address as a string
//
// Returned:    None
//
//********************************************************************'
void sendHelloMulticast (std::string routerIP)
{
	// send multicast packet
	struct in_addr localInterface;
	struct sockaddr_in groupSock;

	int sd;
	std::string multicastAddr = "224.0.0.0";
	ScenicHelloPtr helloPacket = (ScenicHelloPtr) malloc (sizeof(ScenicHello));
	constructPacket(helloPacket,
			((char *)routerIP.c_str()), ((char *)multicastAddr.c_str()), HELLO_SEND);


	/* Create a datagram socket on which to send. */

	sd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sd < 0)
	{
	  perror("Opening datagram socket error");
	  exit(1);
	}

	else
	{
		//printf("Opening the datagram socket...OK.\n");
	}

	/* Initialize the group sockaddr structure with a */
	/* group address of 225.1.1.1 and port 5555. */

	memset((char *) &groupSock, 0, sizeof(groupSock));
	groupSock.sin_family = AF_INET;
	groupSock.sin_addr.s_addr = inet_addr("224.0.0.0");
	groupSock.sin_port = htons(4321);


	/* Set local interface for outbound multicast datagrams. */
	/* The IP address specified must be associated with a local, */
	/* multicast capable interface. */

	localInterface.s_addr = inet_addr((char *)routerIP.c_str());

	if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface,
			sizeof(localInterface)) < 0)

	{
	  perror("Setting local interface error");
	  exit(1);
	}

	else
	{
		//printf("Setting the local interface...OK\n");
	}

	/* Send a message to the multicast group specified by the*/
	/* groupSock sockaddr structure. */

	if(sendto(sd, helloPacket, sizeof(ScenicHello), 0,
			(struct sockaddr*)&groupSock, sizeof(groupSock)) < 0)

	{
		perror("Sending datagram message error");
	}

	else
	{
		printf("\n\Sending datagram message to multicast group from %s...OK\ntime: %s",
		helloPacket->srcAddress, helloPacket->timeSent);
	}

	// free packet
	free (helloPacket);

}
//********************************************************************
// Method:			recvHelloMulticast
//
// Description: listen on the the multicast address to receive a
//							hello packet from the multicast address and send
//							and acknowledgement back to the sender
//
// Parameters:  None
//
// Returned:    the hello packet the was received
//
//********************************************************************'
ScenicHelloPtr recvHelloMulticast (char * routerIP)
{
	struct sockaddr_in localSock;
	struct ip_mreq group;
	int sd;

	/* Create a datagram socket on which to receive. */

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("Opening datagram socket error");
		exit(1);

	}

	else
	{
		//printf("Opening datagram socket....OK.\n");
	}

		/* Enable SO_REUSEADDR to allow multiple instances of this */
		/* application to receive copies of the multicast datagrams. */

	int reuse = 1;

	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
		 sizeof(reuse)) < 0)
	{
		perror("Setting SO_REUSEADDR error");
		close(sd);
		exit(1);
	}

	else
	{
		//printf("Setting SO_REUSEADDR...OK.\n");
	}
	/* Bind to the proper port number with the IP address */

	/* specified as INADDR_ANY. */

	memset((char *) &localSock, 0, sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(4321);
	localSock.sin_addr.s_addr = INADDR_ANY;


	if(bind(sd, (struct sockaddr*)&localSock, sizeof(localSock)))
	{
		perror("Binding datagram socket error");
		close(sd);
		exit(1);
	}

	else
	{
		//printf("Binding datagram socket...OK.\n");
	}
		/* Join the multicast group 226.1.1.1 on the local 203.106.93.94 */
		/* interface. Note that this IP_ADD_MEMBERSHIP option must be */
		/* called for each local interface over which the multicast */
		/* datagrams are to be received. */
	group.imr_multiaddr.s_addr = inet_addr("224.0.0.0");
	group.imr_interface.s_addr = inet_addr(routerIP);

	
	if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group,
		sizeof(group)) < 0)
	{
		
		perror("Adding multicast group error");
		close(sd);
		exit(1);
	}

	else
	{
		//printf("Adding multicast group...OK.\n");
	}

		/* Read from the socket. */
	ScenicHelloPtr packet = (ScenicHelloPtr)malloc(sizeof(ScenicHello));

	if(read(sd, packet, sizeof(ScenicHello)) < 0)
	{
		perror("Reading datagram message error");
		close(sd);
		exit(1);
	}

	else
	{

		printf("Reading hello message...OK.\n");
		printf("The message from multicast server is\nsrc: %s\ndest: %s\ntime: %s\n",
		packet->srcAddress, packet->destAddress, packet->timeSent);

	}

	close(sd);
	return packet;


}
//********************************************************************
// Method:			sendHelloLoop
//
// Description: the loop on the router that sends a hello message
//							every few seconds (determined in .h) to the multicast
//							address
//
// Parameters:  the router IP (as a char *)
//
// Returned:    0 (this is an infinite loop)
//
//********************************************************************'
void * sendHelloLoop (void * routerIP)
{
	std::string thisIP ((char *)routerIP);

	while (true)
	{
		sleep (SEND_INTERVAL);
		sendHelloMulticast(thisIP);
		std::cout << std::endl << std::endl;
	}

	return 0;
}
//********************************************************************
// Method:			recvHelloLoop
//
// Description: the loop on the router waits to get a hello message
//							and returns an ack to the correct address when they
//							receive it
//
// Parameters:  the router IP (as a char *)
//
// Returned:    0 (this is an infinite loop)
//
//********************************************************************'
void * recvHelloLoop (void * routerIP)
{
	int sd;
	char * thisIP = ((char *)routerIP);
	ScenicHelloPtr lastMessage;
	ScenicHelloPtr helloACK;
	struct sockaddr_in localSocket;
	char * ackDestIP;

	while (true)
	{
		// recv a hello packet
		lastMessage = recvHelloMulticast((char *)routerIP);
		std::cout << std::endl << std::endl;

		// acknowledge the hello
		ackDestIP = lastMessage->srcAddress;
		helloACK = (ScenicHelloPtr)malloc(sizeof(ScenicHello));

		// construct a packet from this router, to the one that
		// sent the original hello!
		constructPacket (helloACK, thisIP, ackDestIP, HELLO_ACK);

		// open a datagram socket to send
		sd = socket(AF_INET, SOCK_DGRAM, 0);

		if (sd < 0)
		{
			perror("Opening ACK datagram socket error");
			exit(1);
		}

		else
		{
			printf("Opening the ACK datagram socket...OK.\n");
		}

		memset((char *) &localSocket, 0, sizeof(localSocket));
		localSocket.sin_family = AF_INET;
		localSocket.sin_addr.s_addr = inet_addr(ackDestIP);
		localSocket.sin_port = htons(4321);

		if(sendto(sd, helloACK, sizeof(ScenicHello), 0,
					(struct sockaddr*)&localSocket, sizeof(localSocket)) < 0)

		{
			perror("Sending hello ACK message error");
		}

		else
		{
			printf("Sending hello ACK from %s to %s ...OK\ntime: %s\n\n",
			 helloACK->srcAddress, helloACK->destAddress, helloACK->timeSent);
		}



		free(helloACK);
	}

	close(sd);

	return 0;
}

//********************************************************************
// Method:			recvACKLoop
//
// Description: the function to continuously try to recv a hello ACK
//							using threads and the recvACK function
//
// Parameters:  the router IP (as a void *)
//
// Returned:    0 (this is an infinite loop)
//
//********************************************************************'

void * recvACKLoop (void * routerIP)
{
	ScenicHelloPtr packet;
	while (true)
	{
		packet = recvACK ((char *)routerIP);
		free(packet);
	}
	return 0;
}
//********************************************************************
// Method:			recvACK
//
// Description: the router waits to receive an ACK from a neighbor
//							not from the multicast address. when it receives
//							an ACK, it updates the vector with the new time
//
// Parameters:  the router IP (as a char *)
//
// Returned:    the packet that was received
//
//********************************************************************'
ScenicHelloPtr recvACK (char * routerIP)
{
	int sd;
	struct sockaddr_in recvSocket;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{
		perror("Opening datagram socket error");
		exit(1);

	}

	else
	{
		//printf("Opening datagram socket....OK.\n");
	}

	int reuse = 1;

	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse,
			 sizeof(reuse)) < 0)
	{
		perror("Setting SO_REUSEADDR error");
		close(sd);
		exit(1);
	}

	memset((char *) &recvSocket, 0, sizeof(recvSocket));
	recvSocket.sin_family = AF_INET;
	recvSocket.sin_port = htons(4321);
	recvSocket.sin_addr.s_addr = inet_addr(routerIP);

	if(bind(sd, (struct sockaddr*)&recvSocket, sizeof(recvSocket)))
	{
		perror("Binding datagram socket error");
		close(sd);
		exit(1);
	}

	else
	{
		//printf("Binding datagram socket...OK.\n");
	}
	ScenicHelloPtr packet = (ScenicHelloPtr)malloc(sizeof(ScenicHello));

	if(read(sd, packet, sizeof(ScenicHello)) < 0)
	{
		perror("Reading ACK message error");
		close(sd);
		exit(1);
	}

	else
	{

		printf("Reading ACK...OK.\n");
		printf("The acknowledgement message is\nsrc: %s\ndest:"
						" %s\ntime: %s\ntype: %c\n\n",
		packet->srcAddress, packet->destAddress, packet->timeSent, packet->type);

	}

	return packet;
}

