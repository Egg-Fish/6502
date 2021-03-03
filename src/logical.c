#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "logical.h"

void AND(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    uint8_t addr1;
    uint8_t addr2;

    uint16_t location;
    uint8_t lb, hb;

    addr1 = memory[cpu->PC]; //Low Byte
    (cpu->PC)++;

    switch(opcode){
        case 0x29: //Immediate
            cpu->A = addr1 & cpu->A;
            break;

        case 0x25: //Zero Page
            cpu->A = memory[addr1] & cpu->A;
            break;

        case 0x35: //Zero Page, X
            cpu->A = memory[(addr1 + cpu->X) % 0x100] & cpu->A;
            break;

        case 0x2D: //Absolute
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[location] & cpu->A;
            break;

        case 0x3D: //Absolute, X
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->X) % 0x10000] & cpu->A;
            break;

        case 0x39: //Absolute, Y
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->Y) % 0x10000] & cpu->A;
            break;

        case 0x21: //Indexed Indirect
            //Memory Address is stored in memory[addr1 + X]

            location = indexed_indirect(cpu, memory, addr1);

            cpu->A = memory[location] & cpu->A;
            break;


        case 0x31: //Indirect Indexed
            //Memory Address is stored in memory[addr1], Add Y

            lb = memory[(addr1)% 0x100];
            hb = memory[(addr1 + 1) % 0x100];

            location = (hb << 8) | lb;


            cpu->A = memory[(location + cpu->Y) % 0x10000] & cpu->A;
            break;
    }

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;
}


void EOR(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    uint8_t addr1;
    uint8_t addr2;

    uint16_t location;
    uint8_t lb, hb;

    addr1 = memory[cpu->PC]; //Low Byte
    (cpu->PC)++;

    switch(opcode){
        case 0x49: //Immediate
            cpu->A = addr1 ^ cpu->A;
            break;

        case 0x45: //Zero Page
            cpu->A = memory[addr1] ^ cpu->A;
            break;

        case 0x55: //Zero Page, X
            cpu->A = memory[(addr1 + cpu->X) % 0x100] ^ cpu->A;
            break;

        case 0x4D: //Absolute
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[location] ^ cpu->A;
            break;

        case 0x5D: //Absolute, X
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->X) % 0x10000] ^ cpu->A;
            break;

        case 0x59: //Absolute, Y
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->Y) % 0x10000] ^ cpu->A;
            break;

        case 0x41: //Indexed Indirect
            //Memory Address is stored in memory[addr1 + X]

            location = indexed_indirect(cpu, memory, addr1);

            cpu->A = memory[location] ^ cpu->A;
            break;


        case 0x51: //Indirect Indexed
            //Memory Address is stored in memory[addr1], Add Y

            lb = memory[(addr1)% 0x100];
            hb = memory[(addr1 + 1) % 0x100];

            location = (hb << 8) | lb;


            cpu->A = memory[(location + cpu->Y) % 0x10000] ^ cpu->A;
            break;
    }

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;
}


void ORA(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    uint8_t addr1;
    uint8_t addr2;

    uint16_t location;
    uint8_t lb, hb;

    addr1 = memory[cpu->PC]; //Low Byte
    (cpu->PC)++;

    switch(opcode){
        case 0x09: //Immediate
            cpu->A = addr1 | cpu->A;
            break;

        case 0x05: //Zero Page
            cpu->A = memory[addr1] | cpu->A;
            break;

        case 0x15: //Zero Page, X
            cpu->A = memory[(addr1 + cpu->X) % 0x100] | cpu->A;
            break;

        case 0x0D: //Absolute
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[location] | cpu->A;
            break;

        case 0x1D: //Absolute, X
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->X) % 0x10000] | cpu->A;
            break;

        case 0x19: //Absolute, Y
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            cpu->A = memory[(location + cpu->Y) % 0x10000] | cpu->A;
            break;

        case 0x01: //Indexed Indirect
            //Memory Address is stored in memory[addr1 + X]

            location = indexed_indirect(cpu, memory, addr1);

            cpu->A = memory[location] | cpu->A;
            break;


        case 0x11: //Indirect Indexed
            //Memory Address is stored in memory[addr1], Add Y

            lb = memory[(addr1)% 0x100];
            hb = memory[(addr1 + 1) % 0x100];

            location = (hb << 8) | lb;


            cpu->A = memory[(location + cpu->Y) % 0x10000] | cpu->A;
            break;
    }

    cpu->N = (cpu->A >= 128) ? 1 : 0; //128 == 0b10000000 == -128 (128 doesnt exist, only -128)
    cpu->Z = (cpu->A == 0) ? 1 : 0;

}


void BIT(CPU *cpu, void *m, uint8_t opcode){
    uint8_t *memory = (uint8_t *)m;

    uint8_t addr1;
    uint8_t addr2;

    uint16_t location;
    uint8_t t;

    addr1 = memory[cpu->PC]; //Low Byte
    (cpu->PC)++;

    switch (opcode){
        case 0x24: //Zero Page
            t = cpu->A & memory[addr1];
            break;

        case 0x2C: //Absolute
            addr2 = memory[cpu->PC]; //High Byte
            (cpu->PC)++;

            location = (addr2 << 8) | addr1;

            t = cpu->A & memory[location];
            break;
    }

    cpu->Z = (t == 0) ? 1 : 0;
    cpu->N = (t >= 128) ? 1 : 0;
    cpu->V = (t - 128 >= 64) ? 1 : 0;
}