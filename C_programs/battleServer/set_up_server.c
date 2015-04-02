#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "set_up_server.h"

#ifndef PORT
#define PORT 30100
#endif

/* bind and listen, abort on error
 * returns FD of listening socket
 */
int bindandlisten(void) {
  printf("bindandlisten PORT: %d\n", PORT);
  struct sockaddr_in r;
  int listenfd;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }
  int yes = 1;
  if ((setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))) == -1) {
    perror("setsockopt");
  }
  memset(&r, '\0', sizeof(r));
  r.sin_family = AF_INET;
  r.sin_addr.s_addr = INADDR_ANY;
  r.sin_port = htons(PORT);

  if (bind(listenfd, (struct sockaddr *)&r, sizeof r)) {
    perror("bind");
    exit(1);
  }

  if (listen(listenfd, 5)) {
    perror("listen");
    exit(1);
  }
  return listenfd;
}
