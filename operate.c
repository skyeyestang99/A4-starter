#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "stack.h"
#include "operate.h"

int operate(int pc, instr_t* inst){

    switch (inst->opcode) {
        case PUSH:
        {
            if(check_stack(0,pc)==-1){
                return -1;
            }
            push(inst->operand);
            pc++;
            break;
        }
        case POP:
        {
            int i;
            if(check_stack(1,pc)==-1){
                return -1;
            }
            pop(&i);
            pc++;
            break;
        }
        case SWAP: 
        {
            if(check_stack(2,pc)==-1){
                return -1;
            }
            int x,y;
            pop(&x);
            pop(&y);
            push(x);
            push(y);
            pc++;
            break;
        }
        case PRINTSTACK:
        {
            if(check_stack(1,pc)==-1){
                return -1;
            }
            printstack();
            pc++;
            break;
        }
        case ROT:
        {
            if(check_stack(2,pc)==-1){
                return -1;
            }
            rot();
            pc++;
            break;
        }
        case DUP: 
        {
            if(check_stack(1,pc)==-1){
                return -1;
            }
            int i;
            pop(&i);
            push(i);
            push(i);
            pc++;
            break;
        }
        case GET:
        {
            int val;
            scanf("%d",&val);
            push(val);
            pc++;
            break;
        }
        case PRINT:
        {
            if(check_stack(1,pc)==-1){
                return -1;
            }
            printf("%d\n",head->val);
            pc++;
            break;
        }
        case BTRUE:
        {
            if(check_stack(1,pc)==-1){
                return -1;
            }
            int x;
            pop(&x);
            if(x!=0){
                pc=pc+inst->operand;
                break;
            }
            pc++;
            break;
        }
        case CMPI:
        {
            if(check_stack(1,pc)==-1){
                return -1;
            }
            int x;
            pop(&x);
            if(x==inst->operand){
                push(x);
                push(1);
            }
            else{
                push(x);
                push(0);
            }
            pc++;
            break;
        }
        case HALT:
        {
            delete_stack();
            pc++;
            return -1;
        }
        case ADD:
        {
            if(check_stack(2,pc)==-1){
                return -1;
            }
            int x,y;
            pop(&x);
            pop(&y);
            push(x+y);
            pc++;
            break;
        }
        case SUB:
        {
            if(check_stack(2,pc)==-1){
                return -1;
            }
            int x,y;
            pop(&x);
            pop(&y);
            push(y-x);
            pc++;
            break;
        }
        case MULT:
        {
            if(check_stack(2,pc)==-1){
                return -1;
            }
            int x,y;
            pop(&x);
            pop(&y);
            push(x*y);
            pc++;
            break;
        }
        case NOT:
        {
            if(check_stack(1,pc)==-1){
                return -1;
            }
            int x;
            pop(&x);
            push(!x);
            pc++;
            break;
        }
        default:
            fprintf(stderr, "Illegal opcode 0x%04x at pc %04d\n", inst->opcode, pc);
            exit(EXIT_FAILURE);
    }
    return pc;
}

int check_stack(unsigned int x, int pc) {
    if(size>=x){
        return pc;
    }
    return -1;
}
