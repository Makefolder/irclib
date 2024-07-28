#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "irclib/irc.h"

#define NICKNAME "aegislash525"
#define HOST "irc.freenode.net" // 149.28.246.185
#define ADDRESS "149.28.246.185";
#define PORT 6667

int main(void)
{
    char buff[256];
    const char *serv_addr = ADDRESS;
    int sockfd = establish_conn(serv_addr, PORT);

    read(sockfd, buff, sizeof(buff));
    printf("server says: \n%s\n", buff);

    close(sockfd);
}
