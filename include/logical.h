#ifndef LOGICAL_H
#define LOGICAL_H

void AND(CPU *cpu, void *m, uint8_t opcode);
void EOR(CPU *cpu, void *m, uint8_t opcode);
void ORA(CPU *cpu, void *m, uint8_t opcode);
void BIT(CPU *cpu, void *m, uint8_t opcode);

#endif