///
///  UCSD CSE30 2022
///
#ifndef _STACK_H
/// these are called header guards.  They prevent a .h file from being included
/// in a .c file multiple times.
#define _STACK_H

/// datastructure for one stack entry
///
typedef struct node {
	int val;
	struct node* nxt;
} node_t;

/// push val onto the stack
extern void push(int val);

/// pop val from the stack (return 1 on success, 0 on failure)
extern int pop(int* val);

/// print the stack
extern void printstack();

/// rotate the stack
extern void rot();

/// return the stack size
extern unsigned int get_stack_size();

/// delte the stack
extern void delete_stack();
#endif
