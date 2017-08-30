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
  printDecoder(cpu);
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
  if (control_word & RO) cpu->bus = RAM[cpu->memory_address & 0x0F];
  if (control_word & AO) cpu->bus = cpu->register_A;
  if (control_word & EO) cpu->bus = cpu->alu_output;
  if (control_word & PO) cpu->bus = cpu->program_counter;

  // Now let's have some inputs
  if (control_word & MI) cpu->memory_address = cpu->bus & 0x0F;
  if (control_word & RI) RAM[cpu->memory_address & 0x0F] = cpu->bus;
  if (control_word & II) {
    cpu->register_I = cpu->bus;
    decodeInstruction(cpu);
  }
  if (control_word & AI) {
    cpu->register_A = cpu->bus;
    updateALU(cpu, control_word & SU);
  }
  if (control_word & BI) {
    cpu->register_B = cpu->bus;
    updateALU(cpu, control_word & SU);
  }
  // if (control_word & OI) {
  //   cpu->register_O = cpu->bus;
  //   if(output_hook != NULL) output_hook(cpu->register_O);
  // }
  if (control_word & JP) cpu->program_counter = cpu->bus & 0x0F;

  // Finally do we increment the program counter?
  if (control_word & CE){
    cpu->program_counter = (cpu->program_counter + 1) % RAM_SIZE;
  }
}

void render(CPU *cpu, ram_type RAM) {
  decodeInstruction(cpu);
  executeInstruction(cpu, RAM);

  updateDisplay(cpu, RAM);
}

void step(CPU *cpu, ram_type RAM) {
  if (step_hook != NULL) step_hook();

  render(cpu, RAM);

  cpu->decoder_phase = (cpu->decoder_phase + 1) % PHASE_COUNT;
}

void reset(CPU *cpu) {
  cpu->program_counter = 0;
  cpu->decoder_phase = 0;
  cpu->register_A = 0;
  cpu->register_B = 0;
  cpu->register_I = 0;
  // cpu->register_O = 0;
  cpu->alu_output = cpu->register_A + cpu->register_B;
  cpu->control_word = 0;
}

