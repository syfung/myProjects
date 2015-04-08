#include <stdio.h>
#include <stdlib.h>

#define MAXDIGIT 5

struct index {
  int i;
  int j;
};

struct index findMatch(int *items, int credit, int numItems);
int readNum(char *buf, FILE *inFile);

int main(int argc, char **argv) {
  char *buf;
  buf = malloc(sizeof(char) * MAXDIGIT);

  printf("Done malloc\n");
  
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
  
  printf("Done fopen %s\n", argv[1]);

  int numCase;
  numCase = readNum(buf, inFile);
  printf("Number of Case: %d\n", numCase);

  int credit, numItems, currentCase, i, j;
  int items[2000];
  struct index matchIndex;
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

    matchIndex = findMatch(items, credit, numItems);
    if(matchIndex.i < 0 || matchIndex.j < 0) {
      printf("Matching error\n");
    }

    fprintf(outFile, "Case #%d: %d %d\n", currentCase, matchIndex.i+1, matchIndex.j+1);    
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


struct index findMatch(int *items, int credit, int numItems) {
  int i, j;
  struct index match;
  for(i = 0; i < numItems; i++) {
    for(j = i + 1; j < numItems; j++) {
      if((items[i] + items[j]) == credit) {
	printf("Found the combination at %d, %d, with value %d, %d\n",\
	       i, j, items[i], items[j]);
	printf("Avalabile credit is: %d", credit);
	match.i = i;
	match.j = j;
	return match;
      }
    }
  }
  match.i = -1;
  match.j = -1;
  return match;
}
