#include "instruction.h"
#include "operate.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void printUsage(char* pname) {
	fprintf(stderr, "Usage %s [-th] script\n", pname);
	fprintf(stderr, "\t-t: trace mode\n");
	fprintf(stderr, "\t-h: help\n");
}

int main(int argc, char* argv[]) {
	int opt;
	int trace_mode = 0; // trace instruction as they are executed
	int dissassemble = 0; // disassemble the program
	while ((opt = getopt(argc, argv, "dht")) != -1) {
		switch (opt) {
		case 'd':
			dissassemble = 1;
			break;
		case 'h':
			printUsage(argv[0]);
			return EXIT_SUCCESS;
		case 't':
			trace_mode = 1;
			break;
		default:
			printf("%s unknown option %c\n", argv[0], (char) opt);
			printUsage(argv[0]);
			return EXIT_FAILURE;
		}
	}

	int inum = 0;
	if ((inum = read_program(argv[optind])) == -1) {
		fprintf(stderr, "%s couldn't read code file %s\n", argv[0], argv[optind]);
		return EXIT_FAILURE;
	}

	if (dissassemble) {
		printf("Disassembled program\n");
		for (int i = 0; i < inum; i++) {
			char str[MAX_LINE];
			printf("%s\n", format_instruction(i, str));
		}
		printf("\n");
	}

	printf("Beginning execution\n");
	int pc = 0;
	unsigned int icount = 1;
	while (pc >= 0) {
		int n_pc;
		instr_t* inst = get_instruction(pc);
        if (inst == NULL) {
			printf("Abort at pc = %04d\n", pc);
			break;
		}
		if (trace_mode) {
			char str[MAX_LINE];
			printf("%04d\t%s\n", icount++, format_instruction(pc, str));
		}
		n_pc = operate(pc, inst);
		if (n_pc < 0) {
			printf("Abort at pc = %04d\n", pc);
			break;
		}
		pc = n_pc;
	}
}
