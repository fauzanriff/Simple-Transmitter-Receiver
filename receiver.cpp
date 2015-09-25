//receiver.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

#include "receiver.h"
using namespace std;

//Receiver

int main(int argc, char *argv[]){
//Init
	pthread_t consumer;
	messageXONXOFF = (char*) malloc (1);
	//Input port
	if (argv[1]){
		port = atoi(argv[1]);
		cout << RSay << "listening to : " << port << "\n";
	//Input Handle
	}else{
		cout << RSay << "listening to : 8080 (default)\n";
	}
//Terima Data
	//buat socket dan bind di port
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0){
		cout << RSay << "Socket failed.\n";
	}

	//address structure
	memset(&echoServAddr, 0, sizeof(echoServAddr));		/* Zero out structure */
    echoServAddr.sin_family = AF_INET;                	/* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); 	/* Any incoming interface */
    echoServAddr.sin_port = htons(port);      	/* Local port */

	/* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        cout << RSay << "Bind failed.\n";
	cout << RSay << "Bind to : \t" << port << "\n";

	//buat proses anak
	pthread_create(&consumer, NULL, consumerThread, NULL); //membuat thread konsumsi baru
	//Parent
	while(!allMessageReceived){
		while(kar != '\0' || isImpossibleEndfile){
			/* Set the size of the in-out parameter */
			cliAddrLen = sizeof(echoClntAddr);
			//menangani kemungkinan endfile yang ambigu
			if(kar==SOH || kar==ETX){
				isImpossibleEndfile = true;	//flag bahwa byte berikutnya yang diterima pasti 
											//bukan Endfile walaupun bernilai Endfile
			} else {
				isImpossibleEndfile = false;	//flag bahwa byte berikutnya mungkin Endfile 
											//jika memang bernilai Endfile					
			}
			endFileReceived = -1;
			kar = *(rcvchar(sock, rxq));   	//call rcvchar -> karakter dari socket simpan ke buffer until EOF
		}
	}
	//Diterima endfile yang memang akhir dari pengiriman
    pthread_join(consumer,NULL);
	
	return 0;
}

void *consumerThread(void *args){
	Byte *c = NULL;
	int m = 0;
	while(true){
		c = q_get(rxq);
		if (c != NULL){
			//jika tidak kosong maka periksa apakah byte yang diterima merupakan endfile
			if(!wontConsumingEndfile && (*c)=='\0' && endFileReceived == 2) return NULL;
			//menangani kemungkinan endfile yang ambigu
			if(*c==SOH || *c==ETX){
				wontConsumingEndfile = true;	//flag bahwa byte berikutnya yang diterima pasti 
											//bukan Endfile walaupun bernilai Endfile
			} else {
				wontConsumingEndfile = false;	//flag bahwa byte berikutnya mungkin Endfile 
											//jika memang bernilai Endfile					
			}
			cout << RSay << "Receive " << m++ << "-data : " << c << "\n";
		}
		usleep(DELAY*1000);
		
	}
}

int n = 0;
static Byte *rcvchar(int sockfd, QTYPE *queue){
	Byte *c;

	recvMsgSize = recvfrom(sockfd, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &echoClntAddr, &cliAddrLen);
	if (recvMsgSize < 0){
		cout << RSay << "Receiving message from socket failed.\n";
	}

	c = (Byte*) malloc(sizeof(Byte));

	*c = echoBuffer[0];
	n++;

	if (*c == '\0'){
		endFileReceived = 0;
	}

	//Buffer
	if ((*queue).count < 8){						//pastikan buffer tidak penuh
		if((*queue).count != 0){					//jika buffer tidak kosong
			//menggerakkan bagian belakang queue
			if((*queue).rear==7){					//iterasi rear nya jika sudah paling belakang
				(*queue).rear = 0; 
			} else {								//iterasi rearnya jika masih belum di belakang
				(*queue).rear++;
			}
			((*queue).data)[(*queue).rear] = *c;
		}else{										//jika buffer kosong
			((*queue).data)[(*queue).rear] = *c;
		}
		(*queue).count++;
	}
	
	if ((*queue).count >= MIN_UPPERLIMIT && sent_xonxoff == XON){
		sent_xonxoff = XOFF;
		messageXONXOFF[0] = XOFF;

		if(sendto(sockfd, messageXONXOFF, sizeof(messageXONXOFF), 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != sizeof(messageXONXOFF)){
			cout << RSay << "Sent different number of bytes.\n";
		}
		cout << RSay << "XOFF sent. Counter Buffer > Minimum Upper Limit.\n";
	}
	return c;
}

static Byte *q_get(QTYPE *queue){
	Byte *c = NULL;
	//jika count 0
	if (!queue->count){
		return NULL;
	}else{
		c = (Byte*) malloc (sizeof(Byte)); 
		*c = queue->data[queue->front];
		if (queue->count > 1){
			if(queue->front == 7){
				queue->front = 0;
			}else{
				queue->front++;
			}
		}
		queue->count--;

		//Kirim XON jika dibawah lowerlimit
		if(queue->count <= MAX_LOWERLIMIT && sent_xonxoff == XOFF){
			sent_xonxoff = XON;
			messageXONXOFF[0] = XON;

			if(sendto(sock, messageXONXOFF, sizeof(messageXONXOFF), 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != sizeof(messageXONXOFF)){
				cout << RSay << "Sent different number of bytes.\n";
			}
			cout << RSay << "XON sent. Counter Buffer < Maximum Lower Limit.\n";
		}

	}
	return c;
}

/* Notes : 
* - tambahkan delay antar rcvchar dan q_get() agar terjadi XOFF 
* - receiver jalan lebih dulu sebelum transmitter
* - output harus jelas
* - Header Sample dimasukinnya jangan langsung semua, satu" aja biar ngerti.
*/










