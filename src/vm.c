#include <stdlib.h>

#include "vm.h"
#include "print.h"

void (*output_hook)(unsigned char) = NULL;
void (*step_hook)() = NULL;
void (*halt_hook)() = NULL;

void updateALU(CPU *cpu) {
  cpu->alu_output = (cpu->control_word & SU) ?
    (cpu->register_A - cpu->register_TMP) :
    (cpu->register_A + cpu->register_TMP);
}

void decodeInstruction(CPU *cpu) {
  cpu->control_word = u_instructions[cpu->register_I][cpu->decoder_phase];
  // printRegister8(DECODER_X, DECODER_Y + 3, u_inst);
}

void executeInstruction(CPU *cpu, ram_type RAM) {
  unsigned int control_word = cpu->control_word;

  // Deal with Halt first
  if (control_word & HT) {
    cpu->halt = 1;
    if(halt_hook != NULL) halt_hook();
  }

  // Any time SU, AI, TI are high ALU needs to be updated
  updateALU(cpu);

  /**********
   * OUTPUTS - writing to bus
   **********/
  if (control_word & RO) cpu->bus = RAM[cpu->memory_address & 0xFFFF];
  if (control_word & AO) cpu->bus = cpu->register_A;
  if (control_word & EO) cpu->bus = cpu->alu_output;
  if (control_word & PO) cpu->bus = cpu->program_counter;
  if (control_word & TO) cpu->bus = cpu->register_TMP;
  if (control_word & BO) cpu->bus = cpu->register_B;
  if (control_word & CO) cpu->bus = cpu->register_C;
  if (control_word & V1) cpu->bus = 0x01;

  /*********
   * INPUTS - reading from bus
   ********/
  if (control_word & MI) cpu->memory_address = cpu->bus & 0xFFFF;
  if (control_word & RI) RAM[cpu->memory_address & 0xFFFF] = cpu->bus & 0xFF;
  if (control_word & II) {
    cpu->register_I = cpu->bus & 0xFF;
    decodeInstruction(cpu);
  }
  if (control_word & AI) cpu->register_A = cpu->bus;
  if (control_word & EF) {
    cpu->alu_flags = 0;
    if (cpu->register_A & 0x80) cpu->alu_flags |= ALU_FLAG_S;
    if (cpu->register_A == 0) cpu->alu_flags |= ALU_FLAG_Z;
  }
  if (control_word & BI) cpu->register_B = cpu->bus & 0xFF;
  if (control_word & CI) cpu->register_C = cpu->bus & 0xFF;
  if (control_word & TI) cpu->register_TMP = cpu->bus;
  if (control_word & O3) {
    cpu->port_3 = cpu->bus & 0xFF;
    if(output_hook != NULL) output_hook(cpu->port_3);
  }
  if (control_word & JP) cpu->program_counter = cpu->bus & 0xFFFF;

  // After the input phase update ALU again
  updateALU(cpu);

  /************
   * CONTROL
   ************/
  if (control_word & CE)
    cpu->program_counter = (cpu->program_counter + 1) % RAM_SIZE;


  // Cheat: This should not be inside execute
  printDecoder(cpu);

  // JUMPS
  if (control_word & JZ && cpu->alu_flags & ALU_FLAG_Z)
    cpu->decoder_phase = (cpu->decoder_phase + 2) % PHASE_COUNT;

  if (control_word & JS && cpu->alu_flags & ALU_FLAG_S)
    cpu->decoder_phase = (cpu->decoder_phase + 2) % PHASE_COUNT;
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
  cpu->register_C = 0;
  cpu->register_I = 0;
  cpu->register_TMP = 0;
  cpu->port_3 = 0;
  cpu->alu_output = 0;
  cpu->alu_flags = 0;
  cpu->control_word = 0;
}

