#undef UNICODE
#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 256

using namespace std;
int main(void)
{
	std::cout << "****************\n*    SERVER    *\n****************\n";


	char str[INET_ADDRSTRLEN];

	//Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cout << "WSAStartup failed with error: " << iResult << std::endl;
		return 1;
	}


	//Create a SOCKET for listening for incoming connections request
	SOCKET SrvSocket;
	SrvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SrvSocket == INVALID_SOCKET) {
		std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}


	//The sockaddr_in structure specifies the address family,
	//IP address, and port for the socket that is being bound
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	InetPton(AF_INET, "127.0.0.1", &addrServer.sin_addr.s_addr);
	//InetPton(AF_INET, "192.168.0.20", &addrServer.sin_addr.s_addr);
	addrServer.sin_port = htons(6666);
	memset(&(addrServer.sin_zero), '\0', 8);

	//Bind socket
	if (bind(SrvSocket, (SOCKADDR *)& addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
		std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
		closesocket(SrvSocket);
		WSACleanup();
		return 1;
	}



	//Variables for recieve
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;



	struct sockaddr_in cliAddr;
	int cliAddrLen = sizeof(cliAddr);
	int count = recvfrom(SrvSocket, recvbuf, DEFAULT_BUFLEN, 0, (struct sockaddr *)&cliAddr, &cliAddrLen);


	inet_ntop(AF_INET, &cliAddr.sin_addr, str, INET_ADDRSTRLEN);
	std::cout << "Recieved name from: " << str << std::endl;
	//std::cout << "Recieved: " << recvbuf << std::endl;


	//Create string
	std::string command;
	//std::cout << command << std::endl;
	for (int i = 0; i < count; i++) command = recvbuf;
	cout << "Получена комманад - " << command << endl;


	intelect(command);
	const char* sendbuf = tempc;


	inet_ntop(AF_INET, &cliAddr.sin_addr, str, INET_ADDRSTRLEN);
	std::cout << "Sending size to: " << str << std::endl;

	int c = strlen(sendbuf);
	sendto(SrvSocket, sendbuf, c, 0, (struct sockaddr *)&cliAddr, cliAddrLen);

	// cleanup
	closesocket(SrvSocket);
	WSACleanup();


	getchar();
	return 0;
}
