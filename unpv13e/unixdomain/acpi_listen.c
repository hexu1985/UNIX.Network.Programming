#include	"unp.h"

void 
acpi_cli(int sockfd, const SA *pservaddr, socklen_t servlen);

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_un	cliaddr, servaddr;

	sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

	bzero(&cliaddr, sizeof(cliaddr));		/* bind an address for us */
	cliaddr.sun_family = AF_LOCAL;
	strcpy(cliaddr.sun_path, tmpnam(NULL));

	Bind(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

	bzero(&servaddr, sizeof(servaddr));	/* fill in server's address */
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, "/var/run/acpid.socket");

	acpi_cli(sockfd, (SA *) &servaddr, sizeof(servaddr));

	exit(0);
}

void 
acpi_cli(int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n;
	char	recvline[MAXLINE + 1];

    for ( ; ; ) {
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}
}
