//receiver.cpp
//by fauzan and try

//Problem : Aliran data dari transmitter ke receiver lebih cepat dibandingkan pemrosesan data di receiver.
//Solution : Bentuk sebuah mekanisme aliran data dengan flow control, gunakan bahasa c++.

//Receiver

int main(){}
//Init
//Input port
//Terima Data
//buat socket dan bind di port
//buat proses anak
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
//Proses Data

/* Notes : 
* - tambahkan delay antar rcvchar dan q_get() agar terjadi XOFF 
* - receiver jalan lebih dulu sebelum transmitter
* - output harus jelas
*/










