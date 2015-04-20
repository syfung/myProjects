#include <stdio.h>
#include <stdlib.h>

#include "myStack.h"

static Stack_List *stack_list_top = NULL;

int stack_init() {
  Stack_List *new_list_node;
  int i = 0;

  while(stack_num_inuse(i)) {
    i++;
  }

  new_list_node = malloc(sizeof(Stack_List));
  new_list_node->num = i;
  new_list_node->list_head = NULL;
  new_list_node->next = stack_list_top;
  stack_list_top = new_list_node;

  return i;  
}

int stack_remove();

void stack_push();
int stack_pop();

static int stack_is_emty();
static int stack_is_full();
static void terminate();

static int stack_num_inuse(int num) {
  Stack_List *temp;
  for(temp = stack_list_top; temp; temp = temp->next) {
    if(temp->num == num) {
      return 1;
    }
  }
  return 0;
}
