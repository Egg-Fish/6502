#ifndef STACK_H
#define STACK_H

void TSX(CPU *cpu, void *m, uint8_t opcode);
void TXS(CPU *cpu, void *m, uint8_t opcode);
void PHA(CPU *cpu, void *m, uint8_t opcode);
void PHP(CPU *cpu, void *m, uint8_t opcode);
void PLA(CPU *cpu, void *m, uint8_t opcode);
void PLP(CPU *cpu, void *m, uint8_t opcode);

#endif