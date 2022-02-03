#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "stack.h"

/// operate on the instruction pointed by inst which is located at the given pc.  Return
/// the new PC or -1 if there was an error
///
/// errors may include:
///   insufficent operands on the stack
///   unrecognized instruction.
int operate(int pc, instr_t* inst) {

    switch (inst->opcode) {
        case PUSH: /* perform push expression */
            break;
        case POP: /* perform pop expression */
            break;
            /* add other instruction handling here. */
        default:
            fprintf(stderr, "Illegal opcode 0x%04x at pc %04d\n", inst->opcode, pc);
            exit(EXIT_FAILURE);
    }
}

int check_stack(unsigned int x, int pc) {}
