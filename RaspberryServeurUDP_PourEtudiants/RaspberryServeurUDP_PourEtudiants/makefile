all: TCPRS.exe

main.o: main.cpp
	g++ -Wall -c main.cpp

IRServeurUDP.o: IRServeurUDP.cpp IRServeurUDP.h
	g++ -Wall -c IRServeurUDP.cpp

TCPRS.exe: main.o IRServeurUDP.o
	g++ main.o IRServeurUDP.o -o TCPRS.exe

clean:
#	del -f *.o *.exe
	rm -f *.o TCPRS.exe