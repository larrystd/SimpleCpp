/// server.c
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>		// socket header
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>

#define IP "127.0.0.1"	// IP  address
#define PORT 5000		// port number

int main(int argc, char *argv[])
{
	int lfd, cfd;		// lfd is socket descriptor
	struct sockaddr_in serv_addr, clie_addr;
	socklen_t clie_addr_len;
	char buf[BUFSIZ], clie_ip[BUFSIZ];	//  #define 8192 bytes
	int n, i, ret;

	lfd = socket(AF_INET, SOCK_STREAM, 0);	// SOCK_STREAM means tcp protocol		/* Sequenced, reliable, connection-based byte streams.  */
	if (lfd == -1)
	{
		perror("socket error");
		exit(1);
	}

	/// Construct client address IP+port 127.0.0.1+5000
	bzero(&serv_addr, sizeof(serv_addr));	/// set serv_addr = 0
	serv_addr.sin_family = AF_INET;			// AF_INET means Ipv4 /* IP protocol family.  */
	serv_addr.sin_port = htons(PORT);	// PORT
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	// can accept all local ip

	/// bind serv_addr(ip+port) to socket fd
	ret = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));	
	if (ret == -1)
	{
		perror("bind error");
		exit(1);
	}

	ret = listen(lfd, 128);		/// listen client connection
	if (ret == -1)
	{
		perror("listen error");
		exit(1);
	}

	clie_addr_len = sizeof(clie_addr);
	/// establish connection
	cfd = accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);		/// when client connection, three-way handshake to establish a connection
	/// cfd is connection fd
	printf("client IP: %s, client port: %d\n", 
			inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_ip, sizeof(clie_ip)),
			ntohs(clie_addr.sin_port));

	/// The following is the data transmission process after the connection is established
	int count = 0;
	while (count++ < 2)
	{
		n = read(cfd, buf,  sizeof(buf));		/// read data from client
		for (i = 0; i < n; ++i)
			buf[i] = toupper(buf[i]);	/// Capitalize the input characters
		write(cfd, buf, n);		/// write to client
	}
	/// close cfd, four waves to terminate the connection
	close(cfd);
	close(lfd);
	return 0;
}