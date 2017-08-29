#include "ben.h"

#define PHASE_COUNT 5
#define CONTROL_LINES 15
#define DEFAULT_SLEEP 1024

#define RAM_SIZE 16

#define PRGRM_1 { LDA | 0x0E, ADD | 0x0F, OPT, HLT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 14 }
#define PRGRM_2 { LDI | 0x03, STA | 0x0F, LDI | 0x00, ADD | 0x0F, OPT, JMP | 0x03, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define PRGRM_3 { LDA | 0x0F, OPT, STA | 0x0D, ADD | 0x0E, STA | 0x0F, LDA | 0x0D, STA | 0x0E, JMP | 0x00, 0, 0, 0, 0, 0, 0, 0, 1 }

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

typedef unsigned char ram_type[RAM_SIZE];

int main();
void decodeInstruction(CPU *);
void executeInstruction(CPU *, ram_type);
void updateALU(CPU *, int);
void updateDisplay(const CPU *, const ram_type);
void render(CPU *, ram_type);
void step(CPU *, ram_type);
void reset(CPU *);

extern void (*output_hook)(unsigned char);
extern void (*step_hook)();
extern void (*halt_hook)();
