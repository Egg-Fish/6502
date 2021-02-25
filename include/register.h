#ifndef REGISTER_H
#define REGISTER_H

void TAX(CPU *cpu, void *m, uint8_t opcode);
void TAY(CPU *cpu, void *m, uint8_t opcode);
void TXA(CPU *cpu, void *m, uint8_t opcode);
void TYA(CPU *cpu, void *m, uint8_t opcode);

#endif