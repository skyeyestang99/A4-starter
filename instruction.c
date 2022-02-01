#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static instr_t InstructionMemory[MAXPROG];
static unsigned int lastPC = 0;
// list of operation names (order must match the enum order)
static const char* InstrNames[] = {"push",
	"pop",
	"swap",
	"rot",
	"dup",
	"get",
	"print",
	"printstack",
	"btrue",
	"cmp",
	"halt",
	"add",
	"sub",
	"mult",
	"not"};

instr_t* get_instruction(int pc) {
	instr_t* rc = NULL;
	if ((unsigned) pc <= lastPC && pc >= 0) {
		rc = &InstructionMemory[pc];
	}
	return rc;
}

const char* name_instruction(unsigned int opcode) {
	if (opcode < NUMINSTR) {
		return InstrNames[opcode];
	} else {
		return NULL;
	}
}

/// read the program from a file into our instruction memory
///
/// open the file filename
/// read the program contents into InstructionMemory
/// return -1 on failure
/// else return the number of instrucitons read
int read_program(const char* filename) {
	int rc = 0;
	FILE* fp = NULL;

	if ((fp = fopen(filename, "r")) == NULL) {
		rc = -1;
		goto cleanup;
	}

	size_t n;
	char* buf = NULL;
	char curInstr[MAXLINE];
	int pc = 0;
	while ((getline(&buf, &n, fp)) != -1) {
		int operand;
		int n;
		if ((n = sscanf(buf, "%s %d", curInstr, &operand)) == -1)
			// ignore lines with just whitespace
			continue;

		// skip lines that start with comments
		if (curInstr[0] == '#') continue;
		if (curInstr[0] == '/' && curInstr[1] == '/') continue;

		// look for the instruction
		int found = 0;
		for (unsigned int i = PUSH; i < NUMINSTR; i++) {
			if (strcmp(curInstr, name_instruction(i)) == 0) {
				found = 1;
				InstructionMemory[pc].opcode = i;
				lastPC = pc;
				if (n == 2) {
					InstructionMemory[pc].operand = operand;
				}
				pc = pc + 1;
				curInstr[0] = '\0'; // clear out the current instruction.
				break;
			}
		}
		if (!found) {
			fprintf(stderr, "Unknown instruction(s) %s\n", buf);
			rc = -1;
			goto cleanup;
		}
	}
	rc = pc;
	if (buf != NULL) {
		free(buf);
	}
	fclose(fp);
cleanup:
	return rc;
}

const char* format_instruction(int i, char* str) {
	switch (InstructionMemory[i].opcode) {
	case PUSH:
	case CMPI:
	case BTRUE:
		sprintf(str,
			"%04d : %s %d",
			i,
			name_instruction(InstructionMemory[i].opcode),
			InstructionMemory[i].operand);
		break;
	default:
		sprintf(str, "%04d : %s", i, name_instruction(InstructionMemory[i].opcode));
		break;
	}
	return str;
}
