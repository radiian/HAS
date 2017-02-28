#include "sock.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>


Sock::Sock(sock_type _type, std::string address, int port){
	this->sock_addr.sin_family = AF_INET;
	this->sock_addr.sin_port = htons(port);
	inet_pton(AF_INET, address.c_str(), &this->sock_addr.sin_addr.s_addr);
	this->mode = 1;
	this->type = _type;
	if(this->type == udp){
		this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else{
		if(this->type == tcp){
			this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
		}
	}
	int iSetOption = 1;
	setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR,(char*) &iSetOption, sizeof(iSetOption));
}




Sock::Sock(sock_type _type, int port){
	this->sock_addr.sin_family = AF_INET;
	this->sock_addr.sin_port = htons(port);
	this->sock_addr.sin_addr.s_addr = INADDR_ANY;
	this->mode = 0;
	this->type = _type;
	if(this->type == udp){
		this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else{
		if(this->type == tcp){
			this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
		}
	}


	int iSetOption = 1;
	setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR,(char*) &iSetOption, sizeof(iSetOption));

}


Sock::Sock(sock_type _type){
	this->type = _type;
}

void Sock::Bind(){

	if(bind(this->sockfd, (struct sockaddr *)&this->sock_addr, sizeof(this->sock_addr)) < 0)
	{
		std::cout << "Error on bind" << std::endl;
		this->lasterror = errno;
	}
}

void Sock::Listen(int backlog){
	listen(this->sockfd, backlog);
}

void Sock::Connect(){
	if(connect(this->sockfd, (struct sockaddr *)&this->sock_addr, sizeof(this->sock_addr))< 0){
		std::cout << "Error on connect" << std::endl;
		this->lasterror = errno;
	}
}

Sock Sock::Accept(){
	Sock tmp = Sock(this->type);
	socklen_t socklength = sizeof(tmp.sock_addr);
	tmp.sockfd = accept(this->sockfd, (struct sockaddr *) &tmp.sock_addr, &socklength);
	if(tmp.sockfd < 0){
		std::cout << "Error on accept" << std::endl;
		std::cout << errno << std::endl;
		this->lasterror = errno;
	}
	return tmp;
}

std::string Sock::Read(){
	char buff[256];
	for(int i = 0; i < 255; ++i)buff[i] = 0;
	if(read(this->sockfd, buff, 255) < 0){
		this->lasterror = errno;
		return "";
	}
	std::string tmp = std::string(buff);
	return tmp;

}

void Sock::Write(std::string writedata){
	if(write(this->sockfd, writedata.c_str(), writedata.length()) < 0){
		this->lasterror = errno;
	}

}

void Sock::Close(){
	close(this->sockfd);

}
