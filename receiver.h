/*
* File : receiver.h
*/

#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include "dcomm.h"
using namespace std;

/* Longest string to echo */
#define ECHOMAX 1     
/* Delay to adjust speed of consuming buffer, in milliseconds */
#define DELAY 500
/* Define receive buffer size */
#define RXQSIZE 8
/* Define minimum upperlimit */
#define MIN_UPPERLIMIT 4
/* Define maximum lowerlimit */
#define MAX_LOWERLIMIT 1

/* Global Varible */
string RSay= "Receiver :: ";
unsigned short port=8080;

int sock;							/* Socket */
struct sockaddr_in echoServAddr; 	/* Local address */
struct sockaddr_in echoClntAddr; 	/* Client address */
char echoBuffer[ECHOMAX];        	/* Buffer for echo string */
unsigned int cliAddrLen;         	/* Length of incoming message */
int recvMsgSize;                 	/* Size of received message */

bool allMessageReceived = false;
int endFileReceived;
Byte kar;
bool isImpossibleEndfile = true, wontConsumingEndfile = true;	/* Flag untuk menandai bahwa sebuah Endfile mungkin sebenarnya message number atau checksum */

Byte rxbuf[RXQSIZE];
QTYPE rcvq = { 0, 0, 0, RXQSIZE, rxbuf };
QTYPE *rxq = &rcvq;

char *messageXONXOFF;
Byte sent_xonxoff = XON;			//Boolean send_xon = false, send_xoff = false;

/* Function and Procedure */

void *consumerThread(void *args);
static Byte *rcvchar(int sockfd, QTYPE *queue);
static Byte *q_get(QTYPE *queue);

#endif