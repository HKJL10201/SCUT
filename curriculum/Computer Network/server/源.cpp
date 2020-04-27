#include <winsock.h>
#include <iostream>
#include <stdio.h>
#include <exception>

#pragma comment(lib, "ws2_32.lib")
#define localhost "127.0.0.1"
#define PORT 8080

using namespace std;

struct sockaddr;

int main(int argc, char const* argv[])
{
	WSADATA data;
	SOCKADDR_IN serverSockAddr;
	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET client;
	int status;
	int num_recieve;
	char buffer[1024];
	int addr_len = sizeof(SOCKADDR_IN);

	// initialize
	status = WSAStartup(MAKEWORD(7, 7), &data);
	if (status != 0)
	{
		cout << "error initialize\n";
		return 0;
	}
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_port = htons(PORT);
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.S_un.S_addr = inet_addr(localhost);

	// create socket
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		cout << "error create socket\n";
		return 1;
	}

	// bind
	status = bind(server, (LPSOCKADDR)&serverSockAddr, sizeof(serverSockAddr));
	if (status == SOCKET_ERROR)
	{
		cout << "error binding address\n";
		return 1;
	}

	//listen
	status = listen(server, 10);
	if (status == SOCKET_ERROR)
	{
		cout << "error listening port\n";
		return 1;
	}
	cout << "Start at port: 8080\n";

	//accept
	client = accept(server, (LPSOCKADDR)&serverSockAddr, &addr_len);
	if (client == SOCKET_ERROR)
	{
		cout << "client failed to connect\n";
		return 1;
	}

	// handle
	while (1)
	{
		try
		{
			num_recieve = recv(client, buffer, 1024, 0);
			if (num_recieve == SOCKET_ERROR)
			{
				cout << "Connection terminate!\n";

				if (status == SOCKET_ERROR)
					cout << "error disconnect" << endl;

				status = WSACleanup();
				if (status == SOCKET_ERROR)
					cout << "error clean up" << endl;

				return 1;
			}

			cout << "client's message:" << buffer << endl;

			//closesocket(client);
			cout << "listening...\n";
		}
		catch (const std::exception & e)
		{
			std::cerr << e.what() << '\n';
			return 1;
		}
	}
	closesocket(client);
	return 0;
}