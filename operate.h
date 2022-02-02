///
///  UCSD CSE30 2022
///
#ifndef _OPERATE_H
#define _OPERATE_H
#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"

/// do an operation specified by the instrution pointer
extern int operate(int, instr_t *);
extern int check_stack(unsigned int, int);
#endif
