#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readNum(FILE *inFile);

int main(int argc, char **argv) {
  
  if(argc != 2) {
    printf("Usage: test infile\n");
    exit(1);
  }

  FILE *inFile, *outFile;
  if((inFile = fopen(argv[1], "r")) == NULL) {
    perror("fopen");
    exit(1);
  }
  if((outFile = fopen("ans.txt", "w")) == NULL) {
    perror("fopen");
    exit(1);
  }

  int numCase, maxShy;
  numCase = readNum(inFile);
  printf("\nDone reading num case: %d\n", numCase);

  int currentCase, i;
  for(currentCase = 1; currentCase <= numCase; currentCase++) {
    maxShy = readNum(inFile);
    printf("\nMaximium shyness level of case %d is %d", currentCase, maxShy);
    break;
  }
  
  return 0;
}

int readNum(FILE *inFile) {
  int num, i;
  char *buf, temp;
  buf = malloc(sizeof(char) * 4);

  for(i = 0; (temp = fgetc(inFile)) != '\n'; i++) {
    if(temp == ' ') {
      break;
    }
    
    printf("%c ", temp);
    fflush(stdout);
    
    buf[i] = temp;
  }
  buf[i] = '\0';

  sscanf(buf, "%d", &num);

  return num;
}
