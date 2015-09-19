all : receiver transmitter

receiver :
	g++ -o receiver receiver.cpp

transmitter : 
	g++ -o transmitter transmitter.cpp
