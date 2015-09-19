//receiver.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "ServerSocket.h"
#include "SocketException.h"

using namespace std;

//Receiver - Server

int main(int argc, char *argv[]){
//Init
	string RSay= "Receiver :: ";
	int port=8080;
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
	try{
		ServerSocket server (port);
		while (true) {
			ServerSocket new_sock;
			server.accept (new_sock);
			try{
				while(true){
					string data;
					new_sock >> data;
					cout << RSay << "file received\n";
					new_sock << data;

					//buat proses anak
					pid_t pid = fork();

					if (pid == 0){
						//Child
							//Terima data per-karakter q_get() -dari buffer-
								//check karakter (ada&falid)
								//deteksi emptySpace : nCharInBuffer < maximum lowerlimit
									//YES emptySpace
										//send XON
																	/*
																	*repeat
														            *    if buffer count > 0 then
																	*		read a character from the buffer;
																	*		decrement the buffer count;
																	*		is it a valid character? ( >32, CR, LF atau end-of-file)
																	*until valid character;
																	*if buffer count < maximum lowerlimit then
																	*	send XON to the transmitter;
																	*/
								//Proses Data (buat delay)
					}else if (pid > 0){
						//Parent
							//call rcvchar -> karakter dari socket simpan ke buffer until EOF
								//buffer : circular buffer
								//deteksi overflow : nCharInBuffer > minimum upperlimit
									//YES overflow
										//send XOFF
																	/*
																	*read the character into the buffer and increment the buffer pointers properly;
																	*if the number of characters in the buffer > minimum upperlimit then
																	*	send XOFF to the transmitter;
																	*/
					}else{
						//error Fork
					}
				} //end while
			}catch( SocketException& except ){
				cout << RSay << "exception was caught : " << except.description() << "\n";
			}
		}
	}catch( SocketException& except ){
		cout << RSay << "exception was caught : " << except.description() << "\n";
	}
}

/* Notes : 
* - tambahkan delay antar rcvchar dan q_get() agar terjadi XOFF 
* - receiver jalan lebih dulu sebelum transmitter
* - output harus jelas
* - Header Sample dimasukinnya jangan langsung semua, satu" aja biar ngerti.
*/

/* Reference :
* Socket : http://tldp.org/LDP/LG/issue74/tougher.html
*
*/









