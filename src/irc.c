#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int establish_conn(const char *address, const int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_aton(address, (struct in_addr *) &addr.sin_addr) < 1)
    {
        puts("invalid server address.");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) != 0)
    {
        puts("failed to connect to the server.");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}
