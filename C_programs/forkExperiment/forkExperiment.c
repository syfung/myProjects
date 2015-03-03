#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main () {
  int id, status;

  if ((id = fork()) == 0) {
      printf("child: %d\n", id);
    }

  wait(&status);
  printf("all: %d\n", id);

  return 0;
}
