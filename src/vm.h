#include "ben.h"

#define PHASE_COUNT 5
#define CONTROL_LINES 15
#define DEFAULT_SLEEP 1024

#define PRGRM_1 { LDA | 0x0E, ADD | 0x0F, OPT, HLT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 14 }
#define PRGRM_2 { LDI | 0x03, STA | 0x0F, LDI | 0x00, ADD | 0x0F, OPT, JMP | 0x03, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define PRGRM_3 { LDA | 0x0F, OPT, STA | 0x0D, ADD | 0x0E, STA | 0x0F, LDA | 0x0D, STA | 0x0E, JMP | 0x00, 0, 0, 0, 0, 0, 0, 1, 1 }

typedef struct {
  unsigned char register_A;
  unsigned char register_B;
  unsigned char register_I;
  unsigned char register_O;
  unsigned char program_counter;
  unsigned char memory_address;
  unsigned char alu;
  unsigned char decoder_phase;
  unsigned char bus;
  unsigned short decoder_output;
  unsigned char halt;
} CPU;

extern CPU cpu;
extern unsigned char RAM[16];
extern unsigned int sleep_delay;

int main();
void decodeInstruction(CPU *cpu);
void executeInstruction(CPU *cpu);
void updateALU(CPU *cpu, int);
void updateDisplay(const CPU *cpu);
void step(CPU *cpu);
void reset(CPU *cpu);

extern void (*output_hook)(unsigned char);
