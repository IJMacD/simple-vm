#include <stdlib.h>

#include "vm.h"
#include "print.h"

void (*output_hook)(unsigned char) = NULL;
void (*step_hook)() = NULL;
void (*halt_hook)() = NULL;

void updateALU(CPU *cpu, int subtract) {
  cpu->alu_output = subtract ? (cpu->register_A - cpu->register_B) : (cpu->register_A + cpu->register_B);
}

void updateDisplay(const CPU *cpu, const ram_type RAM) {
  printRegisterA(cpu);
  printRegisterB(cpu);
  printALU(cpu);
  printProgramCounter(cpu);
  printBus(cpu);
  printRam(cpu, RAM);
  printOutput(cpu);
  printInstruction(cpu);
  // printDecoder(cpu);
  printControl(cpu);
  printClock(cpu);
  printRamMap(cpu, RAM);
  printBusGraphic(cpu);
}

void decodeInstruction(CPU *cpu) {
  cpu->control_word = u_instructions[cpu->register_I][cpu->decoder_phase];
  // printRegister8(DECODER_X, DECODER_Y + 3, u_inst);
}

void executeInstruction(CPU *cpu, ram_type RAM) {
  unsigned short control_word = cpu->control_word;

  // Deal with Halt first
  if (control_word & HT) {
    cpu->halt = 1;
    if(halt_hook != NULL) halt_hook();
  }

  // Subtract flag affects ALU output
  updateALU(cpu, control_word & SU);

  // Then we need to deal with outputs
  // note - latest definition wins
  if (control_word & RO) cpu->bus = RAM[cpu->memory_address & 0xFFFF];
  if (control_word & AO) cpu->bus = cpu->register_A;
  if (control_word & EO) cpu->bus = cpu->alu_output;
  if (control_word & PO) cpu->bus = cpu->program_counter;

  // Now let's have some inputs
  if (control_word & MI) cpu->memory_address = cpu->bus & 0xFFFF;
  if (control_word & RI) RAM[cpu->memory_address & 0xFFFF] = cpu->bus & 0xFF;
  if (control_word & II) {
    cpu->register_I = cpu->bus & 0xFF;
    decodeInstruction(cpu);
  }
  if (control_word & AI) {
    cpu->register_A = cpu->bus & 0xFF;
    updateALU(cpu, control_word & SU);
  }
  if (control_word & BI) {
    cpu->register_B = cpu->bus & 0xFF;
    updateALU(cpu, control_word & SU);
  }
  if (control_word & O3) {
    cpu->port_3 = cpu->bus & 0xFF;
    if(output_hook != NULL) output_hook(cpu->port_3);
  }
  if (control_word & JP) cpu->program_counter = cpu->bus & 0xFFFF;

  // Finally do we increment the program counter?
  if (control_word & CE)
    cpu->program_counter = (cpu->program_counter + 1) % RAM_SIZE;

  printDecoder(cpu);

  // For real finally, shall we short circuit the rest of the decoder phases?
  if (control_word & DR){
    cpu->decoder_phase = 0;
  }
  else {
    cpu->decoder_phase = (cpu->decoder_phase + 1) % PHASE_COUNT;
  }
}

void render(CPU *cpu, ram_type RAM) {
  decodeInstruction(cpu);

  updateDisplay(cpu, RAM);
}

void step(CPU *cpu, ram_type RAM) {
  if (step_hook != NULL) step_hook();

  decodeInstruction(cpu);
  executeInstruction(cpu, RAM);

  updateDisplay(cpu, RAM);
}

void reset(CPU *cpu) {
  cpu->program_counter = 0;
  cpu->decoder_phase = 0;
  cpu->memory_address = 0;
  cpu->register_A = 0;
  cpu->register_B = 0;
  cpu->register_I = 0;
  cpu->port_3 = 0;
  cpu->alu_output = cpu->register_A + cpu->register_B;
  cpu->control_word = 0;
}

