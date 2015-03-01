#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "smalloc.h"
#include "testhelpers.h"

#define SIZE 20 * 20


/* Simple test for smalloc and sfree. */

int main(void) {

  mem_init(SIZE);
    
  char *ptrs[20];
  int i;

  /* Call smalloc 4 times */
  printf ("Allocating memory.\n");
  for(i = 0; i < 20; i++) {
    int num_bytes = 20;
    
    if ((ptrs[i] = smalloc(num_bytes)) == NULL) {
      printf ("smalloc fail\n");
      exit (1);
    }
    write_to_mem(num_bytes, ptrs[i], 14);
  }
    
  printf("List of allocated blocks:\n");
  print_allocated();
  printf("List of free blocks:\n");
  print_free();
  printf("Contents of allocated memory:\n");
  print_mem();

  printf("Freeing %p result = %d\n", ptrs[1], sfree(ptrs[4]));
  sfree (ptrs[4]);
  sfree (ptrs[16]);

  printf("List of free blocks:\n");
  print_free();
  
  for(i = 0; i < 20; i++) {
    printf ("Freeing %p, ptr %d\n", ptrs[i], i);
    
    if (sfree(ptrs[i]) == -1) {
      printf (" *** Unable to free ptr %d ***\n", i);
    }
  }
  printf ("\n");
        
  printf("List of allocated blocks:\n");
  print_allocated();
  printf("List of free blocks:\n");
  print_free();
  printf("Contents of allocated memory:\n");
  print_mem();

  printf ("Clear memory\n");
  mem_clean();
  return 0;
}
