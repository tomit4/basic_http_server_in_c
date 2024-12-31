#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Server server_Constructor(int domain, int port, int service,
				 int protocol, int backlog,
				 unsigned long int interface,
				 void (*launch)(struct Server *server))
{
	struct Server server;
	server.domain = domain;
	server.port = port;
	server.service = service;
	server.protocol = protocol;
	server.backlog = backlog;

	server.address.sin_family = domain;
	server.address.sin_port = htons(port);
	server.address.sin_addr.s_addr = htonl(interface);

	server.socket = socket(domain, service, protocol);
	if (server.socket < 0) {
		perror("Failed to initialize/connect to socket...\n");
		exit(EXIT_FAILURE);
	}

	if (bind(server.socket, (struct sockaddr *)&server.address,
		 sizeof(server.address)) < 0) {
		perror("Failed to bind socket...\n");
		exit(EXIT_FAILURE);
	}

	if (listen(server.socket, server.backlog) < 0) {
		perror("Failed to start listening...\n");
		exit(EXIT_FAILURE);
	}

	server.launch = launch;
	return server;
}

void launch(struct Server *server)
{
	char buffer[BUFFER_SIZE];
	while (1) {
		printf("=== WAITING FOR CONNECTION === \n");
		int addrlen = sizeof(server->address);
		int new_socket =
		    accept(server->socket, (struct sockaddr *)&server->address,
			   (socklen_t *)&addrlen);

		if (new_socket < 0) {
			perror("Failed to accept connection");
			continue;
		}

		ssize_t bytesRead = read(new_socket, buffer, BUFFER_SIZE - 1);
		if (bytesRead >= 0) {
			buffer[bytesRead] = '\0'; // Null terminate the string
			puts(buffer);
		} else {
			perror("Error reading buffer...\n");
		}

		FILE *file = fopen("./index.html", "r");
		if (!file) {
			perror("Error opening index.html");
			char *error_response =
			    "HTTP:1.1 500 Internal Server Error\r\n"
			    "Content-Type: text/plain\r\n"
			    "500 Internal Server Error: Failed to open "
			    "index.html";
			write(new_socket, error_response,
			      strlen(error_response));
			close(new_socket);
			continue;
		}

		char file_buffer[BUFFER_SIZE];
		size_t file_size = fread(file_buffer, 1, BUFFER_SIZE - 1, file);

		if (ferror(file)) {
			perror("Error reading index.html");
			char *error_response =
			    "HTTP:1.1 500 Internal Server Error\r\n"
			    "Content-Type: text/plain\r\n"
			    "500 Internal Server Error: Failed to read "
			    "index.html";
			write(new_socket, error_response,
			      strlen(error_response));
			close(new_socket);
			continue;
		}

		file_buffer[file_size] = '\0';
		char response_header[BUFFER_SIZE];
		snprintf(response_header, sizeof(response_header),
			 "HTTP/1.1 200 OK\r\n"
			 "Content-Type: text/html; charset=UTF-8\r\n\r\n");

		write(new_socket, response_header, strlen(response_header));
		write(new_socket, file_buffer, file_size);

		fclose(file);
		close(new_socket);
	}
}
