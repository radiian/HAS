#include <iostream>
#include <thread>

void func(int *test){
	int* ptr= test;
	std::cout << "ptr is " << ptr << std::endl;
	int old = *ptr;	
	std::cout << "The number is " << *ptr << std::endl;
   while(old != 10){
	  int subject = *ptr;
		if(subject != old){
			std::cout << "Value changed!" << std::endl;
			old = subject;
		}
	}
}

int main(){
   std::cout << "Start" << std::endl;
   int r = 3;
   int *rp = &r;
   std::cout << "Starting pointer is " << rp << std::endl;
   std::thread test(func, rp);

   while(r != 10){
	  std::cin >> r;
   }
   test.detach();
}
