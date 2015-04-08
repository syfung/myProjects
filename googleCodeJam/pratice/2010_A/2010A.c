#include <stdio.h>
#include <stdlib.h>

#define MAXDIGIT 5

int readNum(char *buf, FILE *inFile);

int main(int argc, char **argv) {
  char *buf;
  buf = malloc(sizeof(char) * MAXDIGIT);

  printf("Done malloc\n");
  
  if(argc != 2) {
    printf("Usage: test infile\n");
    exit(1);
  }

  FILE *inFile;
  
  if((inFile = fopen(argv[1], "r")) == NULL) {
    perror("fopen");
    exit(1);
  }
  
  printf("Done fopen %s\n", argv[1]);

  int numCase;
  numCase = readNum(buf, inFile);
  printf("Number of Case: %d\n", numCase);

  int credit, numItems, currentCase, i;
  int items[1000];
  for(currentCase = 1; currentCase <= numCase; currentCase++) {
    printf("Current Case: %d\n", currentCase);
    credit = readNum(buf, inFile);
    numItems = readNum(buf, inFile);
    printf("\nCredit: %d\n", credit);
    printf("Items: %d\n", numItems);

    for(i = 0; i < numItems; i++) {
      items[i] = readNum(buf, inFile);
      printf("%d\n", items[i]);
    }
    
  }
  
  

  
  return 0;
}


int readNum(char *buf, FILE *inFile) {
  int temp;
  int charCounter;

  for(charCounter = 0; (temp = getc(inFile)) != '\n'; charCounter++) {
    if(temp == ' ') {
      break;
    }
    printf("%c ", temp);
    fflush(stdout);
    buf[charCounter] = temp;
  }
  
  buf[charCounter] = '\0';
  
  int num;
  sscanf(buf, "%d", &num);
  
  return num;
}
