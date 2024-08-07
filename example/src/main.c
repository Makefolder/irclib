#include <sys/poll.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>

#include "irclib/irc.h"

// EXAMPLE IRC CLIENT
#define NICKNAME "aegislash525"
#define HOST "irc.freenode.net"
#define PORT 6667

#define BUFF_CAPACITY 1024

int main(void)
{
    const char *serv_addr = convert_host(HOST);
    if (serv_addr == NULL)
    {
        puts("ADDRESS NOT FOUND");
        return EXIT_FAILURE;
    }
    // connect to the server
    int sockfd = establish_conn(serv_addr, PORT);

    printf("\n");
    char buff[BUFF_CAPACITY] = { 0 };
    recv(sockfd, buff, sizeof(buff) - 1, 0);
    printf("%s\n", buff);

    authenticate(sockfd, NICKNAME, true);
    struct pollfd fd[2] = {
        {
            0,
            POLLIN,
            0
        },
        {
            sockfd,
            POLLIN,
            0
        }
    };

    // main loop
    while (true)
    {
        char buff[BUFF_CAPACITY] = { 0 };
        poll(fd, 2, 0);
        // input from server
        if (fd[1].revents & POLLIN)
        {
            recv(sockfd, buff, sizeof(buff) - 1, 0);
            printf("%s\n", buff);

            if (strncmp(buff, "PING ", 5) == 0)
                pong(sockfd, buff);
        }
        // input from client
        if (fd[0].revents & POLLIN)
        {
            char send_buff[BUFF_CAPACITY] = { 0 };
            read(0, send_buff, sizeof(send_buff) - 1);
            strncpy(send_buff + strlen(send_buff), "\r\n",
                (sizeof(send_buff) - 1) - strlen(send_buff));

            write(sockfd, send_buff, sizeof(send_buff) - 1);
            printf("sent: %s\n", send_buff);
        }
    }
    close(sockfd);
    return EXIT_SUCCESS;
}
