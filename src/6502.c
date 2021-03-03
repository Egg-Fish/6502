#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "cpu.h"
#include "loadstore.h"
#include "register.h"
#include "stack.h"
#include "logical.h"

#define MAX_MEMORY 65536 //address 0000(0) to FFFF(65535)
#define CLOCK_SPEED 100

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

    // Load Program
    FILE *fp = fopen(argv[1], "rb");

    for (int i = 0; i < MAX_MEMORY; i++){
        uint8_t x = fgetc(fp);
        memory[i] = x;
    }

    fclose(fp);


    //Initialise CPU
    reset(&cpu, memory);
    cpu.CLOCK = CLOCK_SPEED;

    //Logging Info
    FILE *f;
    char location[100] = "logs/";
    strcat(location, argv[1]);
    strcat(location, ".log");

    printf("Log Location = %s\n", location);
    f = fopen(location, "w+");



    while (memory[cpu.PC] != 0){
        uint8_t opcode = memory[cpu.PC];
        cpu.PC++;

        fprintf(f, "\nADDRESS: %04x\nOPCODE: %02x\nExecuting ", cpu.PC-1, opcode);

        //Main Switch
        switch (opcode){
            //----------------LOADSTORE----------------
            //--------LDX--------
            case 0xA9:
            case 0xA5:
            case 0xB5:
            case 0xAD:
            case 0xBD:
            case 0xB9:
            case 0xA1:
            case 0xB1:
                fprintf(f, "LDA\n");
                LDA(&cpu, memory, opcode);
                break;

            //--------LDX--------
            case 0xA2:
            case 0xA6:
            case 0xB6:
            case 0xAE:
            case 0xBE:
                fprintf(f, "LDX\n");
                LDX(&cpu, memory, opcode);
                break;

            //--------LDY--------
            case 0xA0:
            case 0xA4:
            case 0xB4:
            case 0xAC:
            case 0xBC:
                fprintf(f, "LDY\n");
                LDY(&cpu, memory, opcode);
                break;

            //--------STA--------
            case 0x85:
            case 0x95:
            case 0x8D:
            case 0x9D:
            case 0x99:
            case 0x81:
            case 0x91:
                fprintf(f, "STA\n");
                STA(&cpu, memory, opcode);
                break;

            //--------STX--------
            case 0x86:
            case 0x96:
            case 0x8E:
                fprintf(f, "STX\n");
                STX(&cpu, memory, opcode);
                break;

            //--------STY--------
            case 0x84:
            case 0x94:
            case 0x8C:
                fprintf(f, "STY\n");
                STY(&cpu, memory, opcode);
                break;

            //----------------REGISTER----------------
            //--------TAX--------
            case 0xAA:
                fprintf(f, "TAX\n");
                TAX(&cpu, memory, opcode);
                break;
            
            //--------TAY--------
            case 0xA8:
                fprintf(f, "TAY\n");
                TAY(&cpu, memory, opcode);
                break;

            //--------TXA--------
            case 0x8A:
                fprintf(f, "TXA\n");
                TXA(&cpu, memory, opcode);
                break;

            //--------TYA--------
            case 0x98:
                fprintf(f, "TYA\n");
                TYA(&cpu, memory, opcode);
                break;
            
            //----------------STACK----------------
            //--------TSX--------
            case 0xBA:
                fprintf(f, "TSX\n");
                TSX(&cpu, memory, opcode);
                break;

            //--------TXS--------
            case 0x9A:
                fprintf(f, "TXS\n");
                TXS(&cpu, memory, opcode);
                break;

            //--------PHA--------
            case 0x48:
                fprintf(f, "PHA\n");
                PHA(&cpu, memory, opcode);
                break;
            
            //--------PHP--------
            case 0x08:
                fprintf(f, "PHP\n");
                PHP(&cpu, memory, opcode);
                break;

            //--------PLA--------
            case 0x68:
                fprintf(f, "PLA\n");
                PLA(&cpu, memory, opcode);
                break;

            //--------PLP--------
            case 0x28:
                fprintf(f, "PLP\n");
                PLP(&cpu, memory, opcode);
                break;


            //----------------LOGICAL----------------
            //--------AND--------
            case 0x29:
            case 0x25:
            case 0x35:
            case 0x2D:
            case 0x3D:
            case 0x39:
            case 0x21:
            case 0x31:
                fprintf(f, "AND\n");
                AND(&cpu, memory, opcode);
                break;

            //--------EOR--------
            case 0x49: 
            case 0x45: 
            case 0x55:
            case 0x4D:
            case 0x5D: 
            case 0x59:
            case 0x41:
            case 0x51:
                fprintf(f, "EOR\n");
                EOR(&cpu, memory, opcode);
                break;

            //--------ORA--------
            case 0x09:
            case 0x05:
            case 0x15:
            case 0x0D:
            case 0x1D:
            case 0x19:
            case 0x01:
            case 0x11:
                fprintf(f, "ORA\n");
                ORA(&cpu, memory, opcode);
                break;

            //--------BIT--------
            case 0x24:
            case 0x2C:
                fprintf(f, "BIT\n");
                BIT(&cpu, memory, opcode);
                break;

        }

        Sleep(cpu.CLOCK);
    }
    
    print_cpu_status(cpu, f);

    hex_dump(memory, 0x0000, 0xFFFF, f);

    fclose(f);

    free(memory);

    return 0;
}