#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "operate.h"

/*
 * You might want to declare some global variables to
 * help you maintain the stack, and the state of the stack.
 * Once you have implemented push and pop here and corresponding
 * parts in operate.c - we highly recommend checking out
 * tests/stack_test and running it to see if you are getting expected
 * output - to check basic stack functionality. You could write similar
 * tests for other functionalities.
 */
typedef struct node node_t;
node_t *head = NULL;
unsigned int size=0;

/* push a value to the stack */
void push(int val) {
    node_t *newNode = malloc(sizeof(node_t));
    newNode->val = val;
    newNode->next = head;
    head = newNode;
    size++;
}
/* pop a value from the stack
 * return 0 if pop failed, else return 1 and set *v
 */
int pop(int *v) {
    if(head==NULL){
        return 0;
    }
    node_t *temp= malloc(sizeof(node_t));
    *v = (head->val);
    temp = head;
    head=head->next;
    size--;
    free(temp);
    return 1;
}

/* print the entire stack */
void printstack() {
    int index=size-1;
    node_t *cur = malloc(sizeof(node_t));
    cur = head;
    for(int i = size-1;i>=0;i--){
        printf("\tS%d:\t%d\n",index,cur->val);
        cur=cur->next;
        index--;
    }
}

/* the topmost entry becomes the lowest entry in the stack */
void rot() {
    node_t *temp = malloc(sizeof(node_t));
    node_t *cur = malloc(sizeof(node_t));
    cur = head;
    for(int i = size;i>1;i--){
         cur=cur->next;
    }
    temp = head->next;
    cur->next=head;
    cur->next->next=NULL;
    head = temp;
}

/* returns the size of the stack */
unsigned int get_stack_size() {
    return size;
}

/* delete all entries in the stack, free all memory associated with it */
void delete_stack() {
    for(int i = size;i>0;i--){
        node_t *cur = malloc(sizeof(node_t));
         cur=cur->next;
         free(cur);
    }
    free(head);
}
