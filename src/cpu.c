#include <stdint.h>
#include <stdio.h>

#include "cpu.h"

void print_cpu_status(CPU cpu, FILE *f){
    fprintf(f, "Pointers: \n");
    fprintf(f, "PC: %04x\n", cpu.PC);
    fprintf(f, "SP: %04x\n", cpu.SP);

    fprintf(f, "\nRegisters: \n");

    fprintf(f, "A: %02x\n", cpu.A);
    fprintf(f, "X: %02x\n", cpu.X);
    fprintf(f, "Y: %02x\n", cpu.Y);

    fprintf(f, "\nFlags: \n");

    fprintf(f, "NV-BDIZC\n");
    fprintf(f, "%d%d-%d%d%d%d%d\n",cpu.N, cpu.V, cpu.B, cpu.D, cpu.I, cpu.Z, cpu.C);
}

void hex_dump(void *m, uint16_t start, uint16_t end, FILE *f){
    uint8_t *memory = (uint8_t *)m;

    fprintf(f, "\n\n");
    fprintf(f, "ADDRSS:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    fprintf(f, "%#06x: ", start);
    for (int i = start; i < end; i++){
        fprintf(f, "%02x ", memory[i]);
        if ((i+1) % 16 == 0){
            fprintf(f, "\n");
            fprintf(f, "%#06x: ", i+1);
        }
    }
}

void reset(CPU *cpu, void *m){
    uint8_t *memory = (uint8_t *)m;
    uint16_t start = (memory[0xFFFD] << 8) | memory[0xFFFC];

    cpu->PC = start;
    cpu->SP = 0xFF;

    cpu->A = cpu->X = cpu->Y = 0;
    cpu->C = cpu->Z = cpu->I = cpu->D = cpu->B = cpu->V = cpu->N = 0;
}