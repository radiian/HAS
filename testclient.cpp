#include "sock.h"

int main(int argc, char* argv[]){
	std::cout << "Test!" << std::endl;
	Sock testsock = Sock(tcp, "127.0.0.1", 28016);
	testsock.Connect();
	
	std::cout << "Please enter your message: ";
	std::string message = "";
	std::getline(std::cin, message);
	testsock.Write(message);
	
	std::cout << "Server said back: " << testsock.Read() << std::endl;

	testsock.Close();
}
