/********************************************************************
 * The goal of this function is to inplment a a set of sunction to  *
 * create and mantain a dynmamiclly allocated stack structure       *
 *  This version uses a dynamiclly allocted pointer to work         *
 *  I am thinking it might allocate memory every push               *   
 *   Start date: Febuery 6th, 2015 By Joshua See Yui Fung           *
 ********************************************************************/
// Here includes header files
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

// Here includes the custom header files
# include "stackFunction.h"

// The micros are in the header file

// Main starts here, at the moment use this to test your stack
int main (int argc, char **argv) {
  stackStruct *stack_a;
  int size_a;
  printf ("Please enter the size you want to init:");
  scanf ("%d", &size_a);
  //fflush (stdin);
  srand (time(NULL));
  
  if ((stack_a = StackInit (size_a)) == NULL) {
    exit (1);
  }
  
  printf ("%d,%d,%d\n", stack_a->stackTop, stack_a->stackSize, stack_a->mallocTracker);
  
  while (StackPush (stack_a, rand() %MAX_NUMBER +1) >= 0) {
    printf ("%d,%d,%d\n", stack_a->stackTop, stack_a->stackSize, stack_a->mallocTracker);
  }

  while (stack_a->stackTop != -1) {
      printf ("%d, %d\n", StackPop (stack_a), stack_a->stackTop);
  }
  
  StackDestroy (stack_a);
  
  stack_a = NULL;
  return 0;
}

