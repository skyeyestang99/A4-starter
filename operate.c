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
int operate(int pc, instr_t *inst){
}
