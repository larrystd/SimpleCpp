#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/// client application port number is 5000
#define SERV_PORT 5000

int main(int argc, char *argv[])
{
	int cfd;
	struct sockaddr_in serv_addr;
	// socklen_t serv_addr_len;
	char buf[BUFSIZ];
	int n;
    /// cfd
	cfd = socket(AF_INET, SOCK_STREAM, 0);

    /// Construct server address IP+por
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
    /// 127.0.0.1+5000, to connect
	inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr);
    /// Send a connection request to the server, a three-way handshake, and return the correct status code after the connection is successful

	connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /// The following is the data transmission process after the connection is established
	int count = 0;
	while (count++ < 2)
	{
		fgets(buf, sizeof(buf), stdin);
		write(cfd, buf, strlen(buf));
		n = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, n);
	}
    /// Send a connection termination request to the server
	close(cfd);

	return 0;
}