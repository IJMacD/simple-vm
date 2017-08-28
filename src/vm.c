#include "vm.h"
#include "print.h"

unsigned char register_A = 0x00;
unsigned char register_B = 0x00;
unsigned char register_I = 0x00;         // Instruction register
unsigned char register_O = 0x00;         // Output register
unsigned char program_counter = 0x00;
unsigned char memory_address = 0x00;
unsigned char alu = 0x00;
unsigned char RAM[16] = PRGRM_3;
unsigned char decoder_phase = 0x00;
unsigned char bus;
unsigned short decoder_output = 0x00;
unsigned char halt = 0x00;
unsigned int sleep_delay = DEFAULT_SLEEP;

void updateALU(int subtract) {
  if (subtract){
    alu = register_A - register_B;
  } else {
    alu = register_A + register_B;
  }
}

void updateDisplay() {
  printRegisterA();
  printRegisterB();
  printALU();
  printProgramCounter();
  printBus();
  printRam();
  printOutput();
  printInstruction();
  printDecoder();
  printControl();
  printClock();
  printRamMap();
  printBusGraphic();
}

decodeInstruction() {
  unsigned char u_inst = ((register_I & 0xF0) >> 1) | (decoder_phase & 0x07);
  decoder_output = u_instructions[u_inst];
  // printRegister8(DECODER_X, DECODER_Y + 3, u_inst);
}

executeInstruction() {

  // Deal with Halt first
  if (decoder_output & HT) halt = 1;

  // Subtract flag affects ALU output
  updateALU(decoder_output & SU);

  // Then we need to deal with outputs
  // note - latest definition wins
  if (decoder_output & RO) bus = RAM[memory_address & 0x0F];
  if (decoder_output & IO) bus = register_I & 0x0F;
  if (decoder_output & AO) bus = register_A;
  if (decoder_output & EO) bus = alu;
  if (decoder_output & CO) bus = program_counter;

  // Now let's have some inputs
  if (decoder_output & MI) memory_address = bus & 0x0F;
  if (decoder_output & RI) RAM[memory_address & 0x0F] = bus;
  if (decoder_output & II) {
    register_I = bus;
    decodeInstruction();
  }
  if (decoder_output & AI) {
    register_A = bus;
    updateALU(decoder_output & SU);
  }
  if (decoder_output & BI) {
    register_B = bus;
    updateALU(decoder_output & SU);
  }
  if (decoder_output & OI) register_O = bus;
  if (decoder_output & JP) program_counter = bus & 0x0F;

  // Finally do we increment the program counter?
  if (decoder_output & CE) program_counter++;
}

step() {
  decodeInstruction();
  executeInstruction();

  updateDisplay();

  decoder_phase = (decoder_phase + 1) % PHASE_COUNT;
}

reset() {
  program_counter = 0;
  decoder_phase = 0;
  register_A = 0;
  register_B = 0;
  register_I = 0;
  register_O = 0;
  alu = register_A + register_B;
  decoder_output = 0;

  step();
}

