default: sock.cpp sock.h
	g++ sock.cpp -c -o sock.o

demo: testserver.cpp testclient.cpp
	make default
	g++ testclient.cpp sock.o -o client
	g++ testserver.cpp sock.o -o server

clean:
	rm sock.o
	rm client
	rm server
