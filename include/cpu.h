#include <stdint.h>

#ifndef CPU_H
#define CPU_H

typedef struct CPU{
    uint16_t PC;
    uint8_t SP;

    uint8_t A;
    uint8_t X;
    uint8_t Y;

    uint8_t C;
    uint8_t Z;
    uint8_t I;
    uint8_t D;
    uint8_t B;
    uint8_t V;
    uint8_t N;

    uint16_t CLOCK;
} CPU;

void print_cpu_status(CPU cpu, FILE *f);
void hex_dump(void *m, uint16_t start, uint16_t end, FILE *f);
void reset(CPU *cpu, void *m);

uint16_t indexed_indirect(CPU *cpu, uint8_t *memory, uint8_t addr);
uint16_t indirect_indexed(CPU *cpu, uint8_t *memory, uint8_t addr);



#endif