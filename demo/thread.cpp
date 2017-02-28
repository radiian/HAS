#include "../src/sock.h"
#include <iostream>
#include <thread>


void listen(){
  Sock S = Sock(tcp, 28015);
 	S.Bind();
   S.Listen(10);	
   while(true){
	  S.Accept();
	  std::cout << "Accepted client!" << std::endl;
	}
   std::cout << "Quit from inside thread!" << std::endl;
}

int main(){
   //Sock temp = Sock(tcp, 28015);
	std::cout << "Test!" << std::endl;	
	bool run = true;	
	std::thread test(listen);	
	
	std::string input = "";
	while(true){
	   std::cout << "Quit? [y/n]:";
	   std::cin >> input;
	   std::cout << std::endl;
	   if(input == "y"){
		  run = false;
		  break;
	   }
	}
	std::cout << "we are quitting!" << std::endl;
	
}
