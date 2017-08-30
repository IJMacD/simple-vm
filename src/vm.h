#include "ben.h"

#define PHASE_COUNT 5
#define CONTROL_LINES 16
#define DEFAULT_SLEEP 1024

#define RAM_SIZE 65536

#define PRGRM_1 { LDA | 0x0E, ADD | 0x0F, _OUT, HLT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 14 }
#define PRGRM_2 { MVI_A | 0x03, STA | 0x0F, MVI_A | 0x00, ADD | 0x0F, _OUT, JMP | 0x03, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define PRGRM_3 { LDA | 0x0F, _OUT, STA | 0x0D, ADD | 0x0E, STA | 0x0F, LDA | 0x0D, STA | 0x0E, JMP | 0x00, 0, 0, 0, 0, 0, 0, 0, 1 }

typedef struct {
  unsigned short bus;
  unsigned char register_A;
  unsigned char register_B;
  unsigned char register_C;
  unsigned char register_TMP;
  unsigned char register_I;
  unsigned char port_1;
  unsigned char port_2;
  unsigned char port_3;
  unsigned char port_4;
  unsigned char alu_output;
  unsigned char alu_flags;
  unsigned short program_counter;
  unsigned short memory_address;
  unsigned char decoder_phase;
  unsigned int control_word;
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
