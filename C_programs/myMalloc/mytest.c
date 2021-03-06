#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/mman.h>
#include "smalloc.h"


#define SIZE 4096 * 64
#define MAX_NUMBER 100

extern mmapBlock *mem;
extern Block *freelist;
extern Block *allocated_list;

/* Simple test for smalloc and sfree. */

int main(void) {

  mem_init(SIZE);
  
  /*  printf ("address mem pointer: %p\n", mem);
  printf ("mem address of the block: %p\n", mem->addr);
  printf ("mem size: %d\n\n", mem->size);
  */
  
  printf ("freelist address: %p\n", &freelist);
  printf ("freelist pointer address: %p\n", freelist);
  printf ("freelist first address: %p\n", freelist->addr);
  printf ("freelist size: %d\n", freelist->size);
  printf ("freelist next address: %p\n", freelist->next);
  printf ("address of freelist next: %p\n\n", &freelist->next);

  printf ("address mem pointer: %p\n", mem);
  printf ("mem address of the block: %p\n", mem->addr);
  printf ("mem size: %d\n\n", mem->size);

  int *a, *b;
  
  //int i;
  //for (i = 0; i < 20; i ++)
  if ((a = smalloc (sizeof (int) * 20)) == NULL) {
    perror ("smalloc");
    exit(1);
  }
  
  printf ("a address %p\n", a);
  
  //printf ("b address %p\n", b = smalloc (sizeof (int)));
  int i;
  for (i = 0; i < 20; i++) {
    *(a + i) = rand() %MAX_NUMBER +1;
  }

  for (i = 0; i < 20; i++){
    printf ("%d\n", *(a + i));
  }
  sfree (a);
  b = smalloc (sizeof (int) * 20);
  
  printf ("b address %p\n", b);
  
  //printf ("b address %p\n", b = smalloc (sizeof (int)));
  for (i = 0; i < 20; i++) {
    *(b + i) = 20;//rand() %MAX_NUMBER +1;
  }

  for (i = 0; i < 20; i++){
    printf ("%d\n", *(b + i));
  }
  
  
  mem_clean();
  
  /*printf ("address mem pointer: %p\n", mem);
  printf ("mem address of the block: %p\n", mem->addr);
  printf ("mem size: %d\n", mem->size);*/
  
  return 0;
}
