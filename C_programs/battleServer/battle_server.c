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


int main(void) {
  int listenfd;
  listenfd = bindandlisten();

  /* Initialze allset and rset */
  fd_set allset;
  fd_set rset;

  /* Add listenfd to the set of fd passed into select */
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);

  /* Select */
  int clientfd, maxfd, nready;

  /* maxfd identifies how far into the set to search */
  maxfd = listenfd;
  
  /* Accept */
  socklen_t len;
  struct sockaddr_in q;

  /* Client handle */
  struct player *p;
  struct player *head = NULL;

  int i, temp_fd, result;

    while (1) {

    // make a copy of the set before we pass it into select
    rset = allset;

    /* Waiting for input, and error check */
    if ((nready = select(maxfd + 1, &rset, NULL, NULL, NULL)) == -1) {
      perror("select");
      continue;
    }

    /* New connection */
    if (FD_ISSET(listenfd, &rset)){
      printf("A new client is connecting\n");
      len = sizeof(q);

      if ((clientfd = accept(listenfd, (struct sockaddr *)&q, &len)) < 0) {
	perror("accept");
	exit(1);
      }

      /* Adding clientfd to the set */
      FD_SET(clientfd, &allset);

      /* Updating max fd */
      if (clientfd > maxfd) {
	maxfd = clientfd;
      }

      
      printf("Connection from %s\n", inet_ntoa(q.sin_addr));
      head = add_player(head, clientfd, q.sin_addr);
    }

    /* Check all fd in fd_set */
    for(i = 0; i <= maxfd; i++) {

      if (FD_ISSET(i, &rset)) {
	for (p = head; p != NULL; p = p->next) {
	  
	  /* Findind the fd in the list */
	  if (p->fd == i) {
	    printf("Player with fd %d ready to read\n", i);
	    result = handle_player_input(p, head);

	    if (result == -1) {
	      temp_fd = p->fd;
	      head = remove_player(head, p->fd);
	      FD_CLR(temp_fd, &allset);
	      close(temp_fd);
	    }
	    
	    break;
	  }
	}
      }
    }
  }

  
  return 0;
}
