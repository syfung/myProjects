#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#define READY 1
#define NOT_READY 0

#define IN_BATTLE 1
#define NOT_IN_BATTLE 0

void ask_name(int fd);
char *read_name(char **buf, char *input_buf, int added_len);
struct player *find_against(struct player *top);
void set_against (struct player *p, struct player *against);

#endif /* GAME_CONTROL_H */
