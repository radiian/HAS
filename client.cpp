#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void println(string);

int main(int argc, char* argv[]){
	println("This is a test of sockets!");
	
	struct sockaddr_in addr, caddr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(28015);
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	addr.sin_addr.s_addr = INADDR_ANY;
	socklen_t clen;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int csock;
	if(sock < 0){
	   println("Fucked up!");
	   return -1;
	}
	clen = sizeof(caddr);
	if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		println("failed to connect");
	}
	else println("Connected!");
	
	string message = "Test message!";
	cout << "Sending: " << message.c_str() << " With size of: " << message.length() << endl;
	int w = write(sock, message.c_str(), message.length());
	if(w < 0){
		println("Error on send");
		cout << errno << endl;
	}
	else println("Message sent!");
	close(sock);
}

void println(string text){
   std::cout << text << std::endl;
}
