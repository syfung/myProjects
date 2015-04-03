#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct player *find_against(struct player *top) {
  struct player *p;
  for(p = top; p; p = p->next) {
    if (p->in_game == NOT_IN_BATTLE) {
      if (p->ready == READY) {
	return p;
      }
    }
  }
  return NULL;
}

void set_against (struct player *p, struct player *against) {
  p->in_game = IN_BATTLE;
  against->in_game = IN_BATTLE;

   p->against_fd = against->against_fd;
   against->against_fd = p->against_fd;
}
