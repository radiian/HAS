#ifndef SOCK_HEADER
#define SOCK_HEADER
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

enum sock_type{
	tcp,
	udp};

class Sock{
	public:
	int sockfd;// = 0;//File descriptor for the socket
	int lasterror;// = 0;//The last error the socket returned
	int port;// = 0;//The port to connect to or listen on
	int mode;// = 0;//Socket mode. 0 = server, 1 = client;
	int connected;// = 0;//0 = connected, 1 = disconnected
	int maxConnections;// = 10;//Max connections for server to handle
	std::string ip_address;// = "";//The IP address to connect to or liston on
	sock_type type;//Type of socket to create. tcp or udp
	struct sockaddr_in sock_addr;//The address struct for the socket
	
	public:
	Sock(sock_type _type, std::string address, int port);//For client
	Sock(sock_type, int);//For server
	Sock(sock_type);//For accepted client on server
	void Close();
	void Bind();
	void Listen(int);
	void Connect();
	Sock Accept();
	void Write(std::string);
	std::string Read();
};



#endif
