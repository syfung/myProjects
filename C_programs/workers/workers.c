#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WORKERS 2
#define WORKER1 1
#define WORKER2 2

int dowork (int woker_id, int filedes) {





int main () {
  int fd [WORKERS][2];
  pipe (fd[WORKER1]);
  pipe (fd[WORKER2]);

  int who = fork ();
  if (who == 0) {
    /* Worker 1 */
    close (fd[WORKER1][1]);
    close (fd[WORKER2][0]);
    close (fd[WORKER2][1]);

    dowork (fd[WORKER1][0]);
  }
  else if (who > 0) {
    /* Manager needs to spwan one more worker */
    int who2 = fork ();
    if (who2 == 0) {
      /* Worker 2 will get stuff from the manager now */
      clsoe (fd{WORKER2][0]);
      clsoe (fd{WORKER1][0]);
      clsoe (fd{WORKER1][1]);

      do_work (WORKER2, fd[WORKER2][0]);
    }

    else if (who2 > 0) {
      /* Manager sends stuff to workers */
      
