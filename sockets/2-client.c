#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 12345

/**
* main - connects to a listening server. Takes 2 arguments:
*        Usage: 2-client <host> <port>
* @argc: argument count
* @argv: argument array
* Return: 0 on success | 1 on failure
*/
int main(int argc, char **argv)
{
	int client_fd;

	struct sockaddr_in server_addr;
	int port;

	char *host;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		return (1);
	}

	host = argv[1];
	port = atoi(argv[2]);

	client_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (client_fd == -1)
	{
		perror("socket failed");
		return (1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(host);

	if (connect(client_fd, (struct sockaddr *)&server_addr,
	sizeof(server_addr)) == -1)
	{
		close(client_fd);
		return (1);
	}

	printf("Connected to %s:%d\n", host, port);

	close(client_fd);

	return (0);
}
