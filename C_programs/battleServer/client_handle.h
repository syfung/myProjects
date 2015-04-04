#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#define MAX_NAME 10

#define MAX_BUF 1024

struct player {
  int fd;
  int against_fd; /* Against/Previous plyers fd */

  short in_game; /* Flag for in battle */
  short ready; /* Flage for ready */

  int hitpoint;
  int powermove;

  struct in_addr ipaddr;

  char *name;
  char *buf;
  
  struct player *next;
};

struct player *add_player(struct player *top, int fd, struct in_addr addr);
struct player *remove_player(struct player *top, int fd);

void broadcast(struct player *top, int exclude_fd, char *s, int size);
int handle_player_input(struct player *p, struct player *top);

#endif
