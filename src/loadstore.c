#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

void LDA(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    uint8_t addr1;
    uint8_t addr2;

    uint16_t location;
    uint8_t lb, hb;

    addr1 = memory[cpu->PC]; //Low Byte
    (cpu->PC)++;

    switch(opcode){
        case 0xA9: //Immediate
            cpu->A = addr1;
            break;

        case 0xA5: //Zero Page
            cpu->A = memory[addr1];
            break;

        case 0xB5: //Zero Page, X
            cpu->A = memory[(addr1 + cpu->X) % 0x100];
            break;

        case 0xAD: //Absolute
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[location];
            break;

        case 0xBD: //Absolute, X
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->X) % 0x10000];
            break;

        case 0xB9: //Absolute, Y
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->Y) % 0x10000];
            break;

        case 0xA1: //Indexed Indirect
            //Memory Address is stored in memory[addr1 + X]

            lb = memory[(addr1 + cpu->X)% 0x100];
            hb = memory[(addr1 + cpu->X + 1) % 0x100];

            location = (hb << 8) | lb;

            cpu->A = memory[location];
            break;


        case 0xB1: //Indirect Indexed
            //Memory Address is stored in memory[addr1], Add Y

            lb = memory[(addr1)% 0x100];
            hb = memory[(addr1 + 1) % 0x100];

            location = (hb << 8) | lb;


            cpu->A = memory[(location + cpu->Y) % 0x10000];
            break;

            
    }

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;
}