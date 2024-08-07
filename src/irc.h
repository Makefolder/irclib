#include <stdbool.h>

const char* convert_host(const char *host);
int establish_conn(const char *address, const int port);
int authenticate(int sockfd, const char *nickname, bool show_msg);
int pong(int sockfd);
