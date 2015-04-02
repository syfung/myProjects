#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "set_up_server.h"
#include "client_handle.h"
#include "game_control.h"

/*
int main(void) {
  int listenfd;
  listenfd = bindandlisten();

  return 0;
}
*/

int main(void) {
  int clientfd, maxfd, nready;
  struct client *p;
  struct client *head = NULL;
  socklen_t len;
  struct sockaddr_in q;
  struct timeval tv;
  fd_set allset;
  fd_set rset;

  int i;


  int listenfd = bindandlisten();
  // initialize allset and add listenfd to the
  // set of file descriptors passed into select
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);
  // maxfd identifies how far into the set to search
  maxfd = listenfd;

  while (1) {
    // make a copy of the set before we pass it into select
    rset = allset;
    /* timeout in seconds (You may not need to use a timeout for
     * your assignment)*/
    tv.tv_sec = 10;
    tv.tv_usec = 0;  /* and microseconds */

    nready = select(maxfd + 1, &rset, NULL, NULL, &tv);
    if (nready == 0) {
      printf("No response from clients in %ld seconds\n", tv.tv_sec);
      continue;
    }

    if (nready == -1) {
      perror("select");
      continue;
    }

    if (FD_ISSET(listenfd, &rset)){
      printf("a new client is connecting\n");
      len = sizeof(q);
      if ((clientfd = accept(listenfd, (struct sockaddr *)&q, &len)) < 0) {
	perror("accept");
	exit(1);
      }
      FD_SET(clientfd, &allset);
      if (clientfd > maxfd) {
	maxfd = clientfd;
      }
      printf("connection from %s\n", inet_ntoa(q.sin_addr));
      head = addclient(head, clientfd, q.sin_addr);
    }

    for(i = 0; i <= maxfd; i++) {
      if (FD_ISSET(i, &rset)) {
	for (p = head; p != NULL; p = p->next) {
	  if (p->fd == i) {
	    int result = handleclient(p, head);
	    if (result == -1) {
	      int tmp_fd = p->fd;
	      head = removeclient(head, p->fd);
	      FD_CLR(tmp_fd, &allset);
	      close(tmp_fd);
	    }
	    break;
	  }
	}
      }
    }
  }
  return 0;
}
