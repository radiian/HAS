#include "sock.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>


Sock::Sock(sock_type _type, std::string address, int port){
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	inet_pton(AF_INET, address.c_str(), &sock_addr.sin_addr.s_addr);
	mode = 1;
	type = _type;
	if(type == udp){
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else{
		if(type == tcp){
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
		}
	}
}




Sock::Sock(sock_type _type, int port){
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port);
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	mode = 0;
	type = _type;
	if(type == udp){
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else{
		if(type == tcp){
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
		}
	}
}

void Sock::Bind(){
	if(bind(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
	{
		lasterror = errno;
	}
}

void Sock::Listen(int backlog){
	listen(sockfd, backlog);
}
