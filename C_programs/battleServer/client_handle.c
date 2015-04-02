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

struct client *addclient(struct client *top, int fd, struct in_addr addr) {
  struct client *p = malloc(sizeof(struct client));
  if (!p) {
    perror("malloc");
    exit(1);
  }

  printf("Adding client %s\n", inet_ntoa(addr));

  p->fd = fd;
  p->ipaddr = addr;
  p->next = top;
  top = p;
  return top;
}

struct client *removeclient(struct client *top, int fd) {
  struct client **p;

  for (p = &top; *p && (*p)->fd != fd; p = &(*p)->next)
    ;
  // Now, p points to (1) top, or (2) a pointer to another client
  // This avoids a special case for removing the head of the list
  if (*p) {
    struct client *t = (*p)->next;
    printf("Removing client %d %s\n", fd, inet_ntoa((*p)->ipaddr));
    free(*p);
    *p = t;
  } else {
    fprintf(stderr, "Trying to remove fd %d, but I don't know about it\n",
	    fd);
  }
  return top;
}


void broadcast(struct client *top, char *s, int size) {
  struct client *p;
  for (p = top; p; p = p->next) {
    write(p->fd, s, size);
  }
  /* should probably check write() return value and perhaps remove client */
}

int handleclient(struct client *p, struct client *top) {
  char buf[256];
  char outbuf[512];
  int len = read(p->fd, buf, sizeof(buf) - 1);
  if (len > 0) {
    buf[len] = '\0';
    printf("Received %d bytes: %s", len, buf);
    sprintf(outbuf, "%s says: %s", inet_ntoa(p->ipaddr), buf);
    broadcast(top, outbuf, strlen(outbuf));
    return 0;
  } else if (len == 0) {
    // socket is closed
    printf("Disconnect from %s\n", inet_ntoa(p->ipaddr));
    sprintf(outbuf, "Goodbye %s\r\n", inet_ntoa(p->ipaddr));
    broadcast(top, outbuf, strlen(outbuf));
    return -1;
  } else { // shouldn't happen
    perror("read");
    return -1;
  }
}
