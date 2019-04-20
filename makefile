default: sock.cpp sock.h
	g++ sock.cpp -c -o sock.o
clean:
	rm sock.o
