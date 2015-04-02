#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client_handle.h"
#include "game_control.h"

struct player *addplayer(struct player *top, int fd) {
  struct player * player;
  if ((player = malloc(sizeof(struct player))) == NULL) {
    perror("malloc");
    exit(1);
  }

  /* Sent out ask name statment */
  write(fd, "Pick a name:\0", 13);
  
  player->fd = fd;
  player->against = 0;
  player->in_game = NOT_IN_BATTLE;
  player->ready = NOT_READY;
  player->position = 0;
  player->next = top;
  
  top = player;
  
  return top;
}

struct player *removeplayer(struct player *top, int fd);

int playerinput(struct player *player, struct client *top) {
  printf("Reading input\n");
  int len = read(player->fd, &(player->temp[player->position]),	\
		 MAX_TEMP_LEN - 1);

    if (len == 0) {
    /* socket is closed 
    printf("Disconnect from %s\n", inet_ntoa(player->ipaddr));
    sprintf(outbuf, "Goodbye %s\r\n", inet_ntoa(player->ipaddr));
    broadcast(top, outbuf, strlen(outbuf));
  */
    return -1;
    }


  char tempbuf[MAX_TEMP_LEN];
  switch(player->in_game) {

  case IN_BATTLE:
    break;
  case NOT_IN_BATTLE:
    if (player->ready == NOT_READY) {
      printf("Reading input, player not in game not ready\n");
      player->position += len;
     
      memmove(tempbuf, player->temp, player->position + 1);
      tempbuf[player->position + 2] = '\0';
      printf("%s\n", tempbuf);
    }
    break;
  default:
    /* The server is not runing properly */
    printf("in_game: error");
    exit(1);
  }

  return 0;        
}

