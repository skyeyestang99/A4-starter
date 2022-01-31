#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "operate.h"
#include "instruction.h"

void printUsage(char *pname){
  fprintf(stderr, "Usage %s [-th] script\n", pname);
  fprintf(stderr, "\t-t  : trace mode\n");
  fprintf(stderr, "\t-h  : help\n");
}

int main(int argc, char *argv[]){
  int opt;
  int traceMode = 0;     // trace instruction as they are executed
  int dissassemble = 0;  // disassemble the program
  while ((opt = getopt(argc, argv, "dht")) != -1){
    switch (opt) {
    case 'd':
      dissassemble = 1;
      break;
    case 'h':
      printUsage(argv[0]);
      exit(EXIT_SUCCESS);
      break;
    case 't':
      traceMode = 1;
      break;
    default:
      printf("%s unknown option %c\n", argv[0], (char)opt);
      printUsage(argv[0]);
      exit(EXIT_FAILURE);
    }
  }
   
  int numInstructions = 0;
  if ((numInstructions = read_program(argv[optind])) == -1){
    fprintf(stderr, "%s couldn't read code file %s\n", argv[0], argv[optind]);
    exit(EXIT_FAILURE);
  }

  if (dissassemble){
    printf("Disassembled program\n");
    for (int i=0; i<numInstructions; i++){
      char str[MAXLINE];
      printf("%s\n", format_instruction(i, str));
    }    
    printf("\n");
  }

  printf("Beginning execution\n");
  int pc = 0;
  unsigned int instrCount = 1;
  while(pc>=0){
    int nPC;
    instr_t *inst = get_instruction(pc);
    if (traceMode){
      char str[MAXLINE];
      printf("%04d\t%s\n", instrCount++, format_instruction(pc, str));
    }
    nPC = operate(pc, inst);
    if (nPC <0){
      printf("Abort at pc = %04d\n", pc);
      break;
    }
    pc = nPC;
  }
}
