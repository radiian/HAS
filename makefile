default: sock.cpp sock.h
	cd src; \
	g++ sock.cpp -c -o ../bin/sock.o

demo: testserver.cpp testclient.cpp
	make default
	g++ testclient.cpp bin/sock.o -o client
	g++ testserver.cpp bin/sock.o -o server

clean:
	rm bin/sock.o
	rm client
	rm server
