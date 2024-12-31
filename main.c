#include "server.h"

int main(void)
{
	struct Server server = server_Constructor(AF_INET, 8080, SOCK_STREAM, 0,
						  10, INADDR_ANY, launch);
	server.launch(&server);
	return 0;
}
