#include <iostream>
#include <thread>
#include "../src/sock.h"
#include <fcntl.h>
#include <poll.h>


//Great example of nonblocking sockets using poll
//http://www.ibm.com/support/knowledgecenter/ssw_ibm_i_71/rzab6/poll.htm

void call(Sock *s, bool *running){
   	std::cout << "From thread!" << std::endl;
	(*s).Bind();
	(*s).Listen(10);
	std::cout << "We are listening!" << std::endl;
	while(*running == true){
		try{   
		   Sock reader = (*s).Accept();
		   std::cout << "Client connected!" << std::endl;
		}	
	   catch(SNoAccept &e){}//Do nothing as the socket is non blocking
	   catch(SError &e){
		  std::cout << e.what() << std::endl;
	   }
 	}
	std::cout << "Closing!" << std::endl;	
}

int main(){
   	
	//struct pollfd pfd;
	
   
    bool isrun = true;
	bool *r = &isrun;
   	Sock tmp = Sock(tcp, 28016);
	fcntl(tmp.sockfd, F_SETFL, O_NONBLOCK);
	Sock* tmpptr = &tmp;
   	//setup for poll()
	//pfd.fd = tmp.sockfd;
	//pfd.events = POLLIN;
	//poll(&pfd, 1, 100);
	//
	
	std::thread test(call, tmpptr, r);
	std::string msg = "";
	while(true){
		std::cout << "Break? [y\n] ";
		std::cin >> msg;
		if(msg == "y"){
		std::cout << "Closing socket forcefully" << std::endl;
		//tmp.Close();
		close(tmp.sockfd);//Double force close
		break;
		}
	}
	isrun = false;
	std::cout << "Set running to false" << std::endl;
	test.join();
}
