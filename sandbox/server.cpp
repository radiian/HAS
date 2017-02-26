#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

using namespace std;

void println(string);

int main(int argc, char* argv[]){
	println("This is a test of sockets!");
	
	struct sockaddr_in addr, caddr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(28015);
	addr.sin_addr.s_addr = INADDR_ANY;
	socklen_t clen;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int csock;
	
	char buff[256];
	for(int i = 0; i < 255; ++i){
		buff[i] = 0;
	}	
	if(sock < 0){
	   println("Fucked up!");
	   return -1;
	}
	if(bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		println("Failed to bind");
		
	}
	listen(sock, 10);
	clen = sizeof(caddr);
	csock = accept(sock, (struct sockaddr *) &caddr, &clen);
	println("We got a connection!");
	int r = read(csock, buff, 255);
	if(r > 0)
		println("Received:");
	else {
		println("Receive error");
		cout << "Error: " << errno << endl;
	}
	cout << buff << endl;	
	close(sock);
}

void println(string text){
   std::cout << text << std::endl;
}
