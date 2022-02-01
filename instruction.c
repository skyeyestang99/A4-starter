#include "instruction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static instr_t imem[MAX_PROG];
static unsigned int last_pc = 0;
// list of operation names (order must match the enum order)
static const char* inames[] = {
	"push",
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
	"not",
};

instr_t* get_instruction(int pc) {
	instr_t* rc = NULL;
	if ((unsigned) pc <= last_pc && pc >= 0) {
		rc = &imem[pc];
	}
	return rc;
}

const char* name_instruction(unsigned int opcode) {
	if (opcode < NUMINSTR) {
		return inames[opcode];
	} else {
		return NULL;
	}
}

/// read the program from a file into our instruction memory
///
/// open the file filename
/// read the program contents into imem
/// return -1 on failure
/// else return the number of instrucitons read
int read_program(const char* filename) {
	int rc = 0;
	FILE* fp = NULL;

	if ((fp = fopen(filename, "r")) == NULL) return -1;

	size_t n;
	char* buf = NULL;
	char icurrent[MAX_LINE];
	int pc = 0;
	while ((getline(&buf, &n, fp)) != -1) {
		int operand;
		int n;
		// ignore lines with just whitespace
		if ((n = sscanf(buf, "%s %d", icurrent, &operand)) == -1) continue;

		// skip lines that start with comments
		if (icurrent[0] == '#') continue;
		if (icurrent[0] == '/' && icurrent[1] == '/') continue;

		// look for the instruction
		int found = 0;
		for (unsigned int i = PUSH; i < NUMINSTR; i++) {
			if (strcmp(icurrent, name_instruction(i)) == 0) {
				found = 1;
				imem[pc].opcode = i;
				last_pc = pc;
				if (n == 2) {
					imem[pc].operand = operand;
				}
				pc = pc + 1;
				icurrent[0] = '\0'; // clear out the current instruction.
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
cleanup:
	free(buf);
	fclose(fp);
	return rc;
}

const char* format_instruction(int i, char* str) {
	switch (imem[i].opcode) {
	case PUSH:
	case CMPI:
	case BTRUE:
		sprintf(str,
			"%04d : %s %d",
			i,
			name_instruction(imem[i].opcode),
			imem[i].operand
		);
		break;
	default:
		sprintf(str, "%04d : %s", i, name_instruction(imem[i].opcode));
		break;
	}
	return str;
}
