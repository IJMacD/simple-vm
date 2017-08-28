#include "ben.h"

#define PHASE_COUNT 5
#define CONTROL_LINES 15
#define DEFAULT_SLEEP 1024

#define PRGRM_1 { LDA | 0x0E, ADD | 0x0F, OPT, HLT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 14 }
#define PRGRM_2 { LDI | 0x03, STA | 0x0F, LDI | 0x00, ADD | 0x0F, OPT, JMP | 0x03, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

extern unsigned char register_A;
extern unsigned char register_B;
extern unsigned char register_I;
extern unsigned char register_O;
extern unsigned char program_counter;
extern unsigned char memory_address;
extern unsigned char alu;
extern unsigned char RAM[16];
extern unsigned char decoder_phase;
extern unsigned char bus;
extern unsigned short decoder_output;
extern unsigned char halt;
extern unsigned int sleep_delay;

void main();
