#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

void TAX(CPU *cpu, void *m, uint8_t opcode){
    cpu->X = cpu->A; //Implied Addressing

    cpu->N = (cpu->X >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->X == 0) ? 1 : 0;
};

void TAY(CPU *cpu, void *m, uint8_t opcode){
    cpu->Y = cpu->A; //Implied Addressing

    cpu->N = (cpu->Y >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->Y == 0) ? 1 : 0;
};
void TXA(CPU *cpu, void *m, uint8_t opcode){
    cpu->A = cpu->X; //Implied Addressing

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;
};

void TYA(CPU *cpu, void *m, uint8_t opcode){
    cpu->A = cpu->Y; //Implied Addressing

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;
};