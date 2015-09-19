//transmitter.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

//Transmitter

int main(int argc, char *argv[]){
//Init
	string TSay = "Transmitter :: ";
	string host;
	int port;
	string filePath;
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
	//Buat proses anak
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
		//Child
			//terima XON or XOFF
			//baca data recvfrom()
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







