#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

/**
* main - Opens a socket and listens on a port 12345
* Accepts a client connection
* Return: 0 on success, 1 on failure if binding fails
*/
int main(void)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	int enable = 1;

	struct sockaddr_in addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);

	if (server_fd == -1)
	{
		perror("socket failed");
		return (1);
	}

	if (setsockopt(server_fd, SOL_SOCKET,
	SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(int)) < 0)
		perror("SO_REUSEADDR | SO_REUSEPORT failed");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("bind failed");
		return (1);
	}

	if (listen(server_fd, 10) == -1)
	{
		perror("listen failed");
		return (1);
	}

	if (accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len) == -1)
	{
		perror("accept failed");
		return (1);
	}

	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

	close(server_fd);

	return (0);
}
