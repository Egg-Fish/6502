#ifndef LOADSTORE_H
#define LOADSTORE_H

void LDA(CPU *cpu, void *m, uint8_t opcode);
void LDX(CPU *cpu, void *m, uint8_t opcode);
void LDY(CPU *cpu, void *m, uint8_t opcode);

void STA(CPU *cpu, void *m, uint8_t opcode);
void STX(CPU *cpu, void *m, uint8_t opcode);
void STY(CPU *cpu, void *m, uint8_t opcode);

#endif