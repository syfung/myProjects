#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

struct client {
  int fd;
  struct in_addr ipaddr;
  struct client *next;
};

struct client *addclient(struct client *top, int fd, struct in_addr addr);
struct client *removeclient(struct client *top, int fd);
void broadcast(struct client *top, char *s, int size);

int handleclient(struct client *p, struct client *top);

#endif
