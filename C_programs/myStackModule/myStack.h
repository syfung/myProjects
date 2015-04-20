#ifndef MY_STACK_H

#define MY_STACK_H

typedef struct node {
  int data;
  struct node *next;
} Node;

typedef struct stack_list {
  int num;
  Node *list_head;
  struct stack_list *next;
} Stack_List;

int stack_init();
int stack_remove();

void stack_push();
int stack_pop();

static int stack_is_emty();
static int stack_is_full();
static void terminate();
static int stack_num_inuse(int num);

#endif /* MY_STACK_H */
