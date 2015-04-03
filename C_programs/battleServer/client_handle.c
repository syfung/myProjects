#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client_handle.h"
#include "game_control.h"

struct player *add_player(struct player *top, int fd, struct in_addr addr) {
  struct player *p = malloc(sizeof(struct player));
  if (!p) {
    perror("malloc");
    exit(1);
  }

  printf("Adding player %s\n", inet_ntoa(addr));

  ask_name(fd);

  p->fd = fd;
  p->against_fd = 0;
  p->in_game = NOT_IN_BATTLE;
  p->ready = NOT_READY;
  
  p->ipaddr = addr;

  p->name = NULL;
  p->buf = NULL;
  
  p->next = top;
  top = p;

  return top;
}

struct player *remove_player(struct player *top, int fd) {
  struct player **p;
  for (p = &top; *p && (*p)->fd != fd; p = &(*p)->next) {
    ;
  }

  /* Now, p points to (1) top, or (2) a pointer to another client
   * This avoids a special case for removing the head of the list
   */
  if (*p) {
    struct player *t = (*p)->next;
    printf("Removing player %d %s\n", fd, inet_ntoa((*p)->ipaddr));
    free(*p);
    *p = t;
  }

  else {
    fprintf(stderr, "Trying to remove fd %d, but I don't know about it\n",
	    fd);
  }

  return top;
}


void broadcast(struct player *top, int exclude_fd, char *s, int size) {
  struct player *p;
  for (p = top; p; p = p->next) {
    if (p->fd != exclude_fd) {
      write(p->fd, s, size);
    }
  }
  /* should probably check write() return value and perhaps remove client */
}

int handle_player_input(struct player *p, struct player *top) {
  printf("Handleing player %d input\n", p->fd);
  char  outbuf[MAX_BUF], tempbuf[MAX_BUF];
  int len;
  len = read(p->fd, tempbuf, MAX_BUF);
  printf("handle_player_input: Read\n");
  
  if (len == 0) {
    /* socket is closed */
    printf("Disconnect from %s\n", inet_ntoa(p->ipaddr));
    sprintf(outbuf, "\nGoodbye %s\r\n", inet_ntoa(p->ipaddr));
    broadcast(top, p->fd, outbuf, strlen(outbuf));
    return -1;
  }
  
  switch(p->in_game) {

  case IN_BATTLE:
    break;
  case NOT_IN_BATTLE:
    if (!p->ready) {
      printf("handle_player_input: Not ready case buf:%p\n", p->buf);
      
      if ((p->name = read_name(&(p->buf), tempbuf, len)) != NULL) {
	printf("Player %d got a name %s\n", p->fd, p->name);
	sprintf(outbuf, "Player %d got a name %s\n", p->fd, p->name);
	broadcast(top, p->fd, outbuf, strlen(outbuf));

	write(p->fd, "Waiting for opponent...\r\n", 25);
	
	struct player *against;
	if ((against = find_against(top)) != NULL) {
	  printf("Found an oppenete %d for %d\n", against->fd, p->fd);
	  game_init(p, against);
	}
	
	p->ready = READY;
      }
    }
    /* Input form not_in_battle but ready user should be ingored */
    break;
  default:
    /* The server is not runing properly */
    printf("handle_player_input: unexpected in_game FLAG\n");
    exit(1);
  }
  return 0;       
}

