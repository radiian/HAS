#include <iostream>
#include <thread>
#include "../src/sock.h"

void call(Sock s, bool *running){
   	std::cout << "From thread!" << std::endl;
	s.Bind();
	s.Listen(10);
	std::cout << "We are listening!" << std::endl;
	while(*running == true){
   		s.Accept();
		std::cout << "We got a client!" << std::endl;
		std::cout << "Running: " << *running << std::endl;
 	}
	std::cout << "Closing!" << std::endl;	
}

int main(){
   	bool isrun = true;
	bool *r = &isrun;
   	Sock tmp = Sock(tcp, 28016);
   	std::thread test(call, tmp, r);
	std::string msg = "";
	while(true){
		std::cout << "Break? [y\n] ";
		std::cin >> msg;
		if(msg == "y");
		std::cout << "Closing socket forcefully" << std::endl;
		tmp.Close();
		close(tmp.sockfd);//Double force close
		break;
	}
	isrun = false;
	std::cout << "Set running to false" << std::endl;
	test.join();
}
