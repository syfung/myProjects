/********************************************************************************
    CSC209 Assignment 2 C and Pointers -> testhelper.c
    Start: Febuary 9th, 2015
    By: Joshua Fung
*********************************************************************************/
/******************************************************************************************
 *                                   Header files                                         *
 ******************************************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>

/******************************************************************************************
 *                                 Custom Header files                                    *
 ******************************************************************************************/
# include "smalloc.h"
# include "testhelpers.h"

/******************************************************************************************
 *                                   Global varables                                      *
 ******************************************************************************************/
/* Functions prints the datastructures used by smalloc, by asscessing the global varable 
   from smalloc */
extern void *mem;
extern Block *allocated_list;
extern Block *freelist;

/******************************************************************************************
 *                           Content of the functions                                     *
 ******************************************************************************************/
/* Prints each element of the list using the format string given below:*/
void print_list(Block *list) {
  while (list != NULL) {
    printf("[addr: %p, size: %d]\n",list->addr, list->size);
    list = list->next;
  }
  printf("\n");
}

void print_allocated() {
  print_list(allocated_list);
}

void print_free() {
  print_list(freelist);
}

/* write value size times to memory starting at ptr */
void write_to_mem(int size, char *ptr, char value) {
  int i = 0;
  for(i = 0; i < size; i++) {
    ptr[i] = value;
  }
} 

/* Prints the contents of allocated memory. Each byte is printed as two
 * hexadecimal digits. */
void print_mem() {
  Block *cur = allocated_list;
    
  while(cur != NULL) {
    printf("%p: size = %d\n", cur->addr, cur->size);
        
    /* print 16 bytes per line */
    int i, j;
    for(i = 0; i < (cur->size + 8) / 8; i++){
      if((i)%2 == 0){
	printf("%5d:  ", i * 8);
      } else {
	printf("  ");
      }
      for(j = 0; j < 8 && j < (cur->size - (i * 8)); j++) {
		printf("%02x ", *((char *)cur->addr + ((i*8) + j)));
      }
      if((i+1) % 2 == 0 && ((i+1) * 8) != cur->size){
	printf("\n");
      }
    }
    printf("\n");
    cur = cur->next;
  }
  printf("\n");
}
