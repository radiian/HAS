#IF NDEF SOCK_HEADER
#DEFINE SOCK_HEADER

enum sock_type{
	tcp,
	udp};

class Sock{

	int sockfd = 0;//File descriptor for the socket
	int lasterror = 0;//The last error the socket returned
	int port = 0;//The port to connect to or listen on
	string ip_address = "";//The IP address to connect to or liston on
	sock_type type;//Type of socket to create. tcp or udp
	struct sockaddr_in sock_addr;//The address struct for the socket
	
}



#ENDIF
