all : receiver transmitter

receiver :
	g++ -o receiver receiver.cpp ServerSocket.cpp Socket.cpp

transmitter : 
	g++ -o transmitter transmitter.cpp ClientSocket.cpp Socket.cpp
