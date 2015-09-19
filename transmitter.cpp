//transmitter.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

//Transmitter

int main(){}
//Init
	//Input IP Adress, Hostname, Port Number
	//Input File
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


/* Notes : Output harus jelas */