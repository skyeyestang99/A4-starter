#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#define MAX_PROG 256 // max program size
#define MAX_LINE 256 // lines can't be longer than this
// list of possible operations
enum ops_t {
	PUSH = 0,
	POP,
	SWAP,
	ROT,
	DUP,
	GET,
	PRINT,
	PRINTSTACK,
	BTRUE,
	CMPI,
	HALT,
	ADD,
	SUB,
	MULT,
	NOT,
	NUMINSTR
};

//
// instr_t
//
typedef struct instr {
	unsigned int opcode; // instruction operation
	int operand; // instruction operand (if any)
} instr_t;

extern int read_program(const char* filename);
extern instr_t* get_instruction(int PC);
extern const char* name_instruction(unsigned int opcode);
extern const char* format_instruction(int i, char* str);

#endif
