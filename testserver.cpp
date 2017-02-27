#include "sock.h"

int main(int argc, char* argv[]){
	std::cout << "Test!" << std::endl;
	Sock testsock = Sock(tcp, 28016);
	testsock.Bind();
	testsock.Listen(10);
	Sock client = testsock.Accept();
	std::cout << "We have a client!" << std::endl;

	std::string message = client.Read();
	std::cout << "Client said: " << message << std::endl;
	client.Write("Hello back!");

	client.Close();
	testsock.Close();
}
