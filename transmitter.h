/*
* File : transmitter.h
*/

#ifndef _TRANSMITTER_H_
#define _TRANSMITTER_H_

#include <iostream>
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include "dcomm.h"

#define ECHOMAX 1
using namespace std;

string TSay = "Transmitter :: ";
char *host;
unsigned short port;
char *filePath;

int sock;                        	/* Socket descriptor */
struct sockaddr_in echoServAddr; 	/* Echo server address */
struct sockaddr_in fromAddr;     	/* Source address of echo */
unsigned int servAddrLen;         	/* Length of incoming message */

char *echoString;                	/* String to send to echo server */
char echoBuffer[ECHOMAX+1];      	/* Buffer for receiving echoed string */
int echoStringLen;               	/* Length of string to echo */

int recvMsgSize;                 	/* Size of received message */

FILE * pFile;						/* Penampung file yang dibaca */

bool xon = true;

/* Function and Procedure */
void *signerThread(void *args);

#endif