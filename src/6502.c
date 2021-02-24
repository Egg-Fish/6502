#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "cpu.h"
#include "loadstore.h"

#define MAX_MEMORY 65536 //address 0000(0) to FFFF(65535)

/*
 0000-00FF  - RAM for Zero-Page & Indirect-Memory Addressing
 0100-01FF  - RAM for Stack Space & Absolute Addressing
 0200-3FFF  - RAM for programmer use
 4000-7FFF  - Memory mapped I/O
 8000-FFF9  - ROM for programmer useage
 FFFA       - Vector address for NMI (low byte)
 FFFB       - Vector address for NMI (high byte)
 FFFC       - Vector address for RESET (low byte)
 FFFD       - Vector address for RESET (high byte)
 FFFE       - Vector address for IRQ & BRK (low byte)
 FFFF       - Vector address for IRQ & BRK  (high byte) 
*/

int main(int argc, char *argv[]){
    CPU cpu;
    uint8_t *memory;

    // Set up memory
    memory = malloc(MAX_MEMORY);
    memset(memory, 0, MAX_MEMORY);

    // Load Test Program
    FILE *fp = fopen("P:/C/6502/test/testprogram", "rb");

    for (int i = 0; i < MAX_MEMORY; i++){
        uint8_t x = fgetc(fp);
        memory[i] = x;
    }

    fclose(fp);

    reset(&cpu, memory);
    cpu.CLOCK = 1000;

    cpu.Y = 2;

    while (memory[cpu.PC] != 0){
        uint8_t opcode = memory[cpu.PC];
        cpu.PC++;

        printf("\nADDRESS: %04x\nOPCODE: %02x\nExecuting ", cpu.PC-1, opcode);

        //Main Switch
        switch (opcode){
            case 0xA9:
            case 0xA5:
            case 0xB5:
            case 0xAD:
            case 0xBD:
            case 0xB9:
            case 0xA1:
            case 0xB1:
                printf("LDA\n");
                LDA(&cpu, memory, opcode);
                break;

        }

        Sleep(cpu.CLOCK);
    }
    
    print_cpu_status(cpu);
    hex_dump(memory, 0x8000, 0x8010);

    free(memory);

    return 0;
}