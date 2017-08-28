#include <stdlib.h>

#include "vm.h"
#include "print.h"

CPU cpu = {
  .register_A = 0x00,
  .register_B = 0x00,
  .register_I = 0x00,         // Instruction register
  .register_O = 0x00,         // Output register
  .program_counter = 0x00,
  .memory_address = 0x00,
  .alu = 0x00,
  .decoder_phase = 0x00,
  .decoder_output = 0x00,
  .halt = 0x00
};

unsigned char RAM[16] = PRGRM_3;
unsigned int sleep_delay = DEFAULT_SLEEP;

void (*output_hook)(unsigned char) = NULL;

void updateALU(CPU *cpu, int subtract) {
  cpu->alu = subtract ? (cpu->register_A - cpu->register_B) : (cpu->register_A + cpu->register_B);
}

void updateDisplay(const CPU *cpu) {
  printRegisterA(cpu);
  printRegisterB(cpu);
  printALU(cpu);
  printProgramCounter(cpu);
  printBus(cpu);
  printRam(cpu);
  printOutput(cpu);
  printInstruction(cpu);
  printDecoder(cpu);
  printControl(cpu);
  printClock(cpu);
  printRamMap(cpu);
  printBusGraphic(cpu);
}

void decodeInstruction(CPU *cpu) {
  unsigned char u_inst = ((cpu->register_I & 0xF0) >> 1) | (cpu->decoder_phase & 0x07);
  cpu->decoder_output = u_instructions[u_inst];
  // printRegister8(DECODER_X, DECODER_Y + 3, u_inst);
}

void executeInstruction(CPU *cpu) {
  unsigned short decoder_output = cpu->decoder_output;

  // Deal with Halt first
  if (decoder_output & HT) cpu->halt = 1;

  // Subtract flag affects ALU output
  updateALU(cpu, decoder_output & SU);

  // Then we need to deal with outputs
  // note - latest definition wins
  if (decoder_output & RO) cpu->bus = RAM[cpu->memory_address & 0x0F];
  if (decoder_output & IO) cpu->bus = cpu->register_I & 0x0F;
  if (decoder_output & AO) cpu->bus = cpu->register_A;
  if (decoder_output & EO) cpu->bus = cpu->alu;
  if (decoder_output & CO) cpu->bus = cpu->program_counter;

  // Now let's have some inputs
  if (decoder_output & MI) cpu->memory_address = cpu->bus & 0x0F;
  if (decoder_output & RI) RAM[cpu->memory_address & 0x0F] = cpu->bus;
  if (decoder_output & II) {
    cpu->register_I = cpu->bus;
    decodeInstruction(cpu);
  }
  if (decoder_output & AI) {
    cpu->register_A = cpu->bus;
    updateALU(cpu, decoder_output & SU);
  }
  if (decoder_output & BI) {
    cpu->register_B = cpu->bus;
    updateALU(cpu, decoder_output & SU);
  }
  if (decoder_output & OI) {
    cpu->register_O = cpu->bus;
    if(output_hook != NULL) {
      output_hook(cpu->register_O);
    }
  }
  if (decoder_output & JP) cpu->program_counter = cpu->bus & 0x0F;

  // Finally do we increment the program counter?
  if (decoder_output & CE) cpu->program_counter++;
}

void step(CPU *cpu) {
  decodeInstruction(cpu);
  executeInstruction(cpu);

  updateDisplay(cpu);

  cpu->decoder_phase = (cpu->decoder_phase + 1) % PHASE_COUNT;
}

void reset(CPU *cpu) {
  cpu->program_counter = 0;
  cpu->decoder_phase = 0;
  cpu->register_A = 0;
  cpu->register_B = 0;
  cpu->register_I = 0;
  cpu->register_O = 0;
  cpu->alu = cpu->register_A + cpu->register_B;
  cpu->decoder_output = 0;

  step(cpu);
}

