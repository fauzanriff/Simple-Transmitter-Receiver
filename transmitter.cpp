//transmitter.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "ClientSocket.h"
#include "SocketException.h"

using namespace std;

//Transmitter - Client

//Init
string TSay = "Transmitter :: ";
string host, filePath;
int port;

//Form untuk handle ketidak-valid-an input
void inputHandle(){
	cout << TSay << "IP Address/Hostname : ";
	cin >> host;
	cout << TSay << "Port : ";
	cin >> port;
	cout << TSay << "File Path : ";
	cin >> filePath;
}
//Main program
int main(int argc, char *argv[]){

	//Input IP Adress/Hostname, Port Number, File
	if (argc >= 4){
		host = argv[1];
		port = atoi(argv[2]);
		filePath = argv[3];
	//Input Handle
	}else if(argc < 4){
		cout << TSay << "Argumen yang anda berikan kurang lengkap, silahkan lengkapi kembali,";
		inputHandle();
	}else{
		cout << TSay << "Silahkan lengkapi argumen anda,\n";
		inputHandle();
	}
	cout << TSay << "[" << host << "][" << port << "][" << filePath << "]\n";
//Proses Data
	//Buat Socket
		//define address and type
		try{
			ClientSocket client_socket ( host, port );

	     	string reply;
	    	try{
			  	client_socket << "Test message.";
			  	client_socket >> reply;

			  	//Buat proses anak
			  	pid_t pid = fork();

			  	if (pid == 0){
			  		//Child
						//terima XON or XOFF
						//baca data recvfrom()
																		/*
																		*repeat
																		*	ch <- read a character from socket last received char <- ch
																		*	until connection is terminated
																		*/
			  	}else if (pid > 0){
			  		//Parent
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
			  	}else{
			  		//Error Fork
			  	}
					
					

			}catch ( SocketException& except ) {
				cout << TSay << "exception was caught : " << except.description() << "\n";
			}

	      	cout << TSay << "We received this response from the server:\n\"" << reply << "\"\n";

		}catch( SocketException& except ){
			cout << TSay << "exception was caught : " << except.description() << "\n";
		}
}

/* Notes : 
* - Output harus jelas 
* - Header Sample dimasukinnya jangan langsung semua, satu" aja biar ngerti.
*/

/* Reference :
* Socket : http://tldp.org/LDP/LG/issue74/tougher.html
*
*/







