#ifndef server_h
#define server_h

#include <netinet/in.h>

#define BUFFER_SIZE 16000

struct Server {
	int domain;
	int port;
	int service;
	int protocol;
	int backlog;
	unsigned long int interface;

	int socket;
	struct sockaddr_in address;

	void (*launch)(struct Server *server);
};

struct Server server_Constructor(int domain, int port, int service,
				 int protocol, int backlog,
				 unsigned long int interface,
				 void (*launch)(struct Server *server));
void launch(struct Server *server);

#endif
