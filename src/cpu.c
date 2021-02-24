#include <stdint.h>
#include <stdio.h>

#include "cpu.h"

void print_cpu_status(CPU cpu){
    printf("Pointers: \n");
    printf("PC: %04x\n", cpu.PC);
    printf("SP: %04x\n", cpu.SP);

    printf("\nRegisters: \n");

    printf("A: %02x\n", cpu.A);
    printf("X: %02x\n", cpu.X);
    printf("Y: %02x\n", cpu.Y);

    printf("\nFlags: \n");

    printf("C: %01x\n", cpu.C);
    printf("Z: %01x\n", cpu.Z);
    printf("I: %01x\n", cpu.I);
    printf("D: %01x\n", cpu.D);
    printf("B: %01x\n", cpu.B);
    printf("V: %01x\n", cpu.V);
    printf("N: %01x\n", cpu.N);
}

void hex_dump(void *m, uint16_t start, uint16_t end){
    uint8_t *memory = (uint8_t *)m;

    printf("ADDRSS:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    printf("%#06x: ", start);
    for (int i = start; i < end; i++){
        printf("%02x ", memory[i]);
        if ((i+1) % 16 == 0){
            printf("\n");
            printf("%#06x: ", i+1);
        }
    }
}

void reset(CPU *cpu, void *m){
    uint8_t *memory = (uint8_t *)m;
    uint16_t start = (memory[0xFFFD] << 8) | memory[0xFFFC];

    printf("PC set to %04x", start);

    cpu->PC = start;
    cpu->SP = 0x00;

    cpu->A = cpu->X = cpu->Y = 0;
    cpu->C = cpu->Z = cpu->I = cpu->D = cpu->B = cpu->V = cpu->N = 0;
}