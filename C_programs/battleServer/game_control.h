#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 10
#endif /* MAX_NAME_LEN */

#ifndef MAX_TEMP_LEN
#define MAX_TEMP_LEN 512
#endif /* MAX_TEMP_LEN */

#define READY 1
#define NOT_READY 0

#define IN_BATTLE 1
#define NOT_IN_BATTLE 0

struct player {
  int fd; /* Players fd same as in struct client */
  int against; /* Against/Previous plyers fd */
  int in_game; /* 1 yes, 0 no */
  int ready; /* Basicly keep track of does it have a name
	      * or is it speaking */
  char name[MAX_NAME_LEN];
  int position;
  char temp[MAX_TEMP_LEN];
  struct player * next;
};

struct player * addplayer(struct player *top, int fd);
struct player *removeplayer(struct player *top, int fd);

int playerinput(struct player *player, struct client *top);

#endif /* GAME_CONTROL_H */
