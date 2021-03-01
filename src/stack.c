#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "stack.h"

void TSX(CPU *cpu, void *m, uint8_t opcode){
    cpu->X = cpu->SP;
    cpu->N = (cpu->X >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->X == 0) ? 1 : 0;
}

void TXS(CPU *cpu, void *m, uint8_t opcode){
    cpu->SP = cpu->X;
}

void PHA(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;
    uint16_t location = 0x0100 | cpu->SP;

    memory[location] = cpu->A;
    (cpu->SP)--;
}

void PHP(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;
    uint16_t location = 0x0100 | cpu->SP;

    uint8_t flags = (cpu->N << 7) | (cpu->V << 6) | (0 << 5) | (cpu->B << 4) | (cpu->D << 3) | (cpu->I << 2) | (cpu->Z << 1) | (cpu->C);

    memory[location] = flags;
    (cpu->SP)--;
}


void PLA(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    (cpu->SP)++;
    uint16_t location = 0x0100 | cpu->SP;

    cpu->A = memory[location];

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;
}

void PLP(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    (cpu->SP)++;
    uint16_t location = 0x0100 | cpu->SP;

    uint8_t flags = memory[location];

    cpu->N = (flags/2/2/2/2/2/2/2 % 2 == 0) ? 0 : 1;
    cpu->V = (flags/2/2/2/2/2/2 % 2 == 0) ? 0 : 1;

    cpu->B = (flags/2/2/2/2 % 2 == 0) ? 0 : 1;
    cpu->D = (flags/2/2/2 % 2 == 0) ? 0 : 1;
    cpu->I = (flags/2/2 % 2 == 0) ? 0 : 1;
    cpu->Z = (flags/2 % 2 == 0) ? 0 : 1;
    cpu->C = (flags % 2 == 0) ? 0 : 1;
}
