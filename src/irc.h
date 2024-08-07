#include <stdbool.h>

int establish_conn(const char *address, const int port);
int authenticate(int sockfd, const char *nickname, bool show_msg);
int pong(int sockfd);
