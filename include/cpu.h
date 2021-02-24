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

void print_cpu_status(CPU cpu);
void hex_dump(void *m, uint16_t start, uint16_t end);
void reset(CPU *cpu, void *m);




#endif