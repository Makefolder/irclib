#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>


#define CMD_BUFSIZE 512

const char* convert_host(const char *host)
{
    struct addrinfo filter;
    struct addrinfo *result;

    memset(&filter, 0, sizeof(filter));
    filter.ai_family = AF_INET;
    filter.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host, NULL, &filter, &result);
    if (status)
    {
        puts("irclib::convert_host: Failed to convert host to IPv4.");
        return NULL;
    }

    void *addr;
    char *address = (char *) calloc(INET_ADDRSTRLEN, sizeof(char));
    addr = &((struct sockaddr_in *) result->ai_addr)->sin_addr;
    inet_ntop(result->ai_family, addr, address, INET_ADDRSTRLEN);

    freeaddrinfo(result);
    return address;
}

int establish_conn(const char *address, const int port)
{
    if (address == NULL)
    {
        puts("irclib::establish_conn: Address cannot be NULL.");
        return -1;
    }

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

// NICK aegislash525
// USER aegislash525 0 * :aegislash525
int authenticate(int sockfd, const char *nickname, bool show_msg)
{
    if (nickname == NULL)
    {
        puts("irclib::authenticate: Nickname cannot be NULL.");
        return -1;
    }
    size_t bufsize = CMD_BUFSIZE;
    char *nickname_cmd = (char *) malloc(sizeof(char) * bufsize);
    char *user_cmd = (char *) malloc(sizeof(char) * bufsize);
    if ((strlen(nickname) * 2) + 11 >= bufsize)
    {
        bufsize *= 2;
        if ((strlen(nickname) * 2) + 13  > bufsize)
        {
            puts("irclib::authenticate: Do you realy need double of bufsize just for your nickname?");
            return -1;
        }
        char *ptr = (char *) realloc(nickname_cmd, sizeof(char) * bufsize);
        if (ptr == NULL)
        {
            puts("irclib::authenticate: Failed to reallocate memory for nickname command.");
            return -1;
        }
        nickname_cmd = ptr;
        char *ptr2 = (char *) realloc(user_cmd, sizeof(char) * bufsize);
        if (ptr2 == NULL)
        {
            puts("irclib::authenticate: Failed to reallocate memory for user command.");
            return -1;
        }
        user_cmd = ptr2;
    }

    snprintf(nickname_cmd, bufsize, "NICK %s\r\n", nickname);
    snprintf(user_cmd, bufsize, "USER %s 0 * :%s\r\n", nickname, nickname);

    char **commands = (char **) malloc(sizeof(char) * 2);
    commands[0] = nickname_cmd;
    commands[1] = user_cmd;

    for (size_t i = 0; i < 2; i++)
    {
        char *command = commands[i];
        send(sockfd, command, strlen(command), 0);
        if (show_msg)
            printf("client > %s\n", command);
        free(command);
    }
    free(commands);
    return 0;
}

int pong(int sockfd)
{
    send(sockfd, "pong\r\n", sizeof(char) * 4, 0);
    return 0;
}
