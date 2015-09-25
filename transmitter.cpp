//transmitter.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

#include "transmitter.h"
using namespace std;

//Transmitter

int main(int argc, char *argv[]){
//Init

	pthread_t signer;						/* Thread */
	bool connect = true;


	//Input IP Adress/Hostname, Port Number, File
	if (argv[1]&&argv[2]&&argv[3]){
		host = argv[1];
		port = atoi(argv[2]);
		filePath = argv[3];
	//Input Handle
	}else{
		cout << TSay << "Please input information below,\n";
		cout << TSay << "IP Address/Hostname : ";
		cin >> host;
		cout << TSay << "Port : ";
		cin >> port;
		cout << TSay << "File Path : ";
		cin >> filePath;
	}
	cout << TSay << "[" << host << "][" << port << "][" << filePath << "]\n";
//Proses Data
    
    //Buat Socket
    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        cout << TSay << "Socket failed.\n";	
	cout << TSay << "Socket to " << host << " : " << port << "\n";
    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));    	/* Zero out structure */
    echoServAddr.sin_family = AF_INET;                 	/* Internet addr family */
    echoServAddr.sin_addr.s_addr = inet_addr(host);  	/* Server IP address */
    echoServAddr.sin_port   = htons(port);     			/* Server port */
	
	//Buat proses anak
	pthread_create(&signer,NULL,signerThread,NULL);

	echoString = (char*)malloc(1);

	//Parent
		//open File
	int n;
	pFile=fopen (filePath,"r");
	if (pFile == NULL){
		cout << TSay << "File failed to open.\n";
		exit(0);
	}else{
		cout << TSay << "File opened.\n";
		n = 0;
		int c;
		while (true){
			if (xon){
				c = fgetc(pFile);
				char sendChar[2];
				sendChar[0] = c;

				if(sendto(sock, sendChar, sizeof(sendChar), 0, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) != sizeof(sendChar)){
					cout << TSay << "Sent different number of bytes.\n";
				}

				cout << TSay << "Sent " << n++ << "-data : " << c << " to the socket.\n";
				if(c == EOF){
					connect = false;
					break;
				}
			}else{
				//wait
			}
		}
	}
	return 0;
		//Kirim Data ketika XON
			//Untuk setiap File
				//Kirim 1 karakter sendto()
														/*
														*while not end of file do
														*	if last received char is not XOFF then
														*	ch <- read a character from file send ch through socket
														*/
		//Ketika XOFF
			//Tunggu sinyal XON
}

void *signerThread(void *args){
	servAddrLen = sizeof(echoServAddr);
	//Child
	while (connect){
		//terima XON or XOFF
		recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &echoServAddr, &servAddrLen);
		if (recvMsgSize < 0){
			cout << TSay << "Receiving message from socket failed.\n";
		}
			//baca data recvfrom()
		if(echoBuffer[0] == XON){
			xon = true;
			cout << TSay << "Receive XON Signal.\n";
		}else if(echoBuffer[0] == XOFF){
			xon = false;
			cout << TSay << "Receive XOFF Signal.\n";
		}
	}
														/*
														*repeat
														*	ch <- read a character from socket last received char <- ch
														*	until connection is terminated
														*/
}

/* Notes : 
* - Output harus jelas 
* - Header Sample dimasukinnya jangan langsung semua, satu" aja biar ngerti.
*/







