#include <stdio.h>
#include <stdlib.h>

#ifndef MAXSIZE
  #define MAXSIZE 60
#endif

#ifndef MAXLINE
  #define MAXLINE 120
#endif

int main (int argc, char **argv) {
  char **numbers;
  int i, j;
  numbers = malloc(sizeof(char *) * (MAXLINE));
  *(numbers) = malloc(sizeof(char) * MAXSIZE);

  if (argc < 2 || argv[1] == NULL) {
    printf("Usage: test file.txt\n");
    exit(1);
  }

  FILE *readNumFile;
  if ((readNumFile = fopen(argv[1], "r")) == NULL) {
    perror("fopen");
    exit(1);
  }

  printf("Before loop\n");
  for (i = 0; fgets(*(numbers + i), MAXSIZE, readNumFile) != NULL;\
       i++) {
    *(numbers + 1 + i) = malloc(sizeof(char) * MAXSIZE);
    printf("Working %d\n", i);
    for (j = 0; j < MAXSIZE; j++) {
      if (*(*(numbers + i) + j) == '\n') {
	*(*(numbers + i) + j) = '\0';
	break;
      }
    }
  }
  
  *(numbers + 1 + i) = NULL;
  
  for (i = 0; *(numbers + i) != NULL; i++) {
    printf("%s\n", *(numbers + i));
  }
  
  for (i = 0; i < 100; i++) {
    free(*(numbers + i));
  }

  free(numbers);
  
  return 0;
}
