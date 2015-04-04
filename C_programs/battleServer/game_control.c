#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client_handle.h"
#include "game_control.h"

void ask_name(int fd) {
  write(fd, "Enter your name:", 16);
}

char *read_name(char **buf, char *input_buf, int added_len) {
  int i, size;
  char *p;
  
  if (*buf == NULL) {
    *buf = malloc(sizeof(char));
    *buf[0] = '\0';
  }
  
  for(i = 0; i < added_len; i++) {
    if (input_buf[i] == '\n') {
      printf("read_name: a newline is found ");
      size = strlen(*buf);
      p = malloc(size + added_len + 1);
      memmove(p, *buf, size);
      memmove(&p[size], input_buf, i);
      p[size + i] = '\0';
      printf("read_name: %s\n", p);

      free(*buf);
      *buf = NULL;
      return p;
    }
  }
  printf("read_name: No newline found\n");

  
  size = strlen(*buf);
  p = malloc(size + added_len + 1);
  memmove(p, *buf, size);
  memmove(&p[size], input_buf, added_len);
  p[size + added_len] = '\0';
  printf("read_name: %s\n", p);

  free(*buf);
  *buf = p;
  return NULL;
}

struct player *find_against(struct player *p, struct player *top) {
  struct player *temp;
  for(temp = top; temp; temp = temp->next) {
    if(temp->in_game == NOT_IN_BATTLE) {
      if(temp->ready == READY) {
	if(temp != p->against_p) {
	  if(temp != p) {
	    return temp;
	  }
	}
      }
    }
  }
  return NULL;
}

void game_init(struct player *p, struct player *against) {
  char outbuf[MAX_BUF];
  srand(time(NULL));
  
  set_against(p, against);
  init_hit_power(p);
  init_hit_power(against);

  /* Notifing p, found oppounet */
  sprintf(outbuf, "\nYou engaged %s\r\n", against->name);
  write(p->fd, outbuf, strlen(outbuf));

  /* Notifing against, found oppounet */
  sprintf(outbuf, "\nYou engaged %s\r\n", p->name);
  write(against->fd, outbuf, strlen(outbuf));

  /* Notifing p the asigned hitpoint and powermove */
  sprintf(outbuf, "Your hitpoint: %d\nYour powermove: %d\n"\
	  , p->hitpoint, p->powermove);
  write(p->fd, outbuf, strlen(outbuf));
  
  /* Notifing p oppounet's hitpoint */
  sprintf(outbuf, "\n** %s's **\nhitpoint: %d\n"\
	  , against->name, against->hitpoint);
  write(p->fd, outbuf, strlen(outbuf));

  /* Notifing against the asigned hitpoint and powermove */
  sprintf(outbuf, "Your hitpoint: %d\nYour powermove: %d\n"\
	  , against->hitpoint, against->powermove);
  write(against->fd, outbuf, strlen(outbuf));

  /* Notifing against oppounet's hitpoint */
  sprintf(outbuf, "\n** %s's **\nhitpoint: %d\n"\
	  , p->name, p->hitpoint);
  write(against->fd, outbuf, strlen(outbuf));

  players_turn(p, against);
  
  printf("Game for %s and %s is set\n", p->name, against->name);
}

void set_against (struct player *p, struct player *against) {
  p->in_game = IN_BATTLE;
  against->in_game = IN_BATTLE;
    
  p->against_p = against;
  against->against_p = p;
}

void init_hit_power(struct player *p) {    
  p->hitpoint = rand() % (22 - 13 + 1) + 13;
  p->powermove = rand() % (4 - 0 + 1) + 0;
}

void players_turn(struct player *p, struct player *against) {
  char outbuf[MAX_BUF];
  
  /* Notifing p it is his turn to strik */
  sprintf(outbuf, "\nIt is your trun\n(A)ttack\n(P)owermove\n(S)peak\nInput move: \n");
  write(against->fd, outbuf, strlen(outbuf));

  /* Notifing against to wait to strik */
  sprintf(outbuf, "\nIt is %s's turn!\n",against->name);
  write(p->fd, outbuf, strlen(outbuf));

  p->turn = WAIT;
  against->turn = TURN;
}

void dead(struct player *dead, struct player *won) {
  char outbuf[MAX_BUF];
  
  /* Notifing  */
  sprintf(outbuf, "\nYou died\nWaiting for new opponet...\n");
  write(dead->fd, outbuf, strlen(outbuf));

  /* Notifing  */
  sprintf(outbuf, "\nYou won\nWaiting for new opponet...\n");
  write(won->fd, outbuf, strlen(outbuf));

  dead->in_game = NOT_IN_BATTLE;
  won->in_game = NOT_IN_BATTLE;
}

int attack_move(struct player *p, struct player *against) {
  char outbuf[MAX_BUF];

  /* Notifing */
  sprintf(outbuf, "\n%s used attack\n",p->name);
  write(against->fd, outbuf, strlen(outbuf));
  
  against->hitpoint = against->hitpoint - (rand() % (6-1 +1)+1);

  if(against->hitpoint < 0) {
    dead(against, p);
    return -1;
  }
  
  /* Notifing */
  sprintf(outbuf, "You have %d hitpoint left\n",against->hitpoint);
  write(against->fd, outbuf, strlen(outbuf));
  
  /* Notifing against oppounet's hitpoint */
  sprintf(outbuf, "\n** %s's **\nhitpoint: %d\n"\
	  , against->name, against->hitpoint);
  write(p->fd, outbuf, strlen(outbuf));

  players_turn(p, against);

  return 0;
}
int powermove_move(struct player *p, struct player *against) {
  char outbuf[MAX_BUF];

  if(p->powermove < 1) {
    sprintf(outbuf, "\nYou have no more power move left\nYou wasted a turn");
    write(p->fd, outbuf, strlen(outbuf));
    players_turn(p, against);
    return 0;
  }

  p->powermove = p->powermove - 1;
  

  /* Notifing */
  sprintf(outbuf, "\nYou used powermove\n");
  write(p->fd, outbuf, strlen(outbuf));

  /* Notifing */
  sprintf(outbuf, "\n%s used powermove\n",p->name);
  write(against->fd, outbuf, strlen(outbuf));

  int dam;
  if((rand() % (1+6+1)-6) < 0) {
    dam = (rand() % (15-10+1)+10);
    against->hitpoint = against->hitpoint - dam;

    if(against->hitpoint <= 0) {
      dead(against, p);
      return -1;
    }
   
    sprintf(outbuf,\
	    "\nYour powermove hited %s\n** %s's **\nhitpoint: %d\n"\
	    , against->name, against->name, against->hitpoint);
    write(p->fd, outbuf, strlen(outbuf));

    /* Notifing against oppounet's hitpoint */
    sprintf(outbuf, "%s's powermove hited you\nYour hitpoint: %d\n"\
	    , p->name, against->hitpoint);
    write(against->fd, outbuf, strlen(outbuf));
  }
  else {
    /* Notifing against oppounet's hitpoint */
    sprintf(outbuf, "%s used powermove but missed\n"\
	    , p->name);
    write(against->fd, outbuf, strlen(outbuf));

    /* Notifing against oppounet's hitpoint */
    sprintf(outbuf, "\nYou missed");
    write(p->fd, outbuf, strlen(outbuf));
  }
  
  players_turn(p, against);

  return 0;
}

void speak_move(struct player *p) {

}
