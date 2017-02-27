#include "sock.h"

int main(int argc, char* argv[]){
	std::cout << "Test!" << std::endl;
	Sock testsock = Sock(tcp, "127.0.0.1", 28016);
	testsock.Connect();
	testsock.Write("Hello there!");
	
	std::cout << "Server said back: " << testsock.Read() << std::endl;

	testsock.Close();
}
