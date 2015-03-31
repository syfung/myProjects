#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  FILE *readFile, *ans;

  printf("Opening file: %s\n", argv[1]);
  readFile = fopen(argv[1],"r");
  if (readFile == NULL) {
    perror("fopen");
  }

  ans = fopen("ans.txt","w");

  printf("Allocating Space\n");
  int size = 6000;
  int items[2000];
  char temp[6000];

  printf("Reading file\n");
  int numCase;
  printf("%s",fgets(temp, 10, readFile));
  fflush(stdout);
  
  numCase = (int)strtol(temp, NULL, 10);
  printf("%d\n", numCase);
  
  int i, j, count, credit = 0, numItems = 0;
  int offset = 0;
  char *num;  
  
  for (i = 1, offset = 0; i <= numCase; i++) {
    fprintf(ans, "Case #%d: ", i);
    fgets(temp, size - 1, readFile);
    credit = (int)strtol(temp, NULL, 10);
    printf("credit: %d\n", credit);
    fgets(temp, size - 1, readFile);
    numItems = (int)strtol(temp, NULL, 10);
    fgets(temp, size - 1, readFile);
    printf("%s", temp);

    for (j = 0; temp[j] != '\0'; j++) {
      if (temp[j] == ' ' || temp[j] == '\n') {
	temp[j] = '\0';
      }
    }
    printf("%s, %p\n", temp, &temp);
    num = temp;
    printf("%s, %p\n", num, num);
    for (count = 0; count < numItems; count++) {
      items[count] = strtol(num, &num, 10);
      num += 1;
    }
    
    for (j = 0; j < numItems; j++) {
      printf("%d ", items[j]);
    }
    printf("\n");

    for (j = 0; j < numItems; j++) {
      for (count = j + 1; count < numItems; count++) {
	if ((items[j] + items[count]) == credit) {
	  printf("%d %d", j + 1, count + 1);
	  fprintf(ans,"%d %d\n", j + 1, count + 1);
	}
      }
    }
  }
  fclose(readFile);

  return 0;
}

    
