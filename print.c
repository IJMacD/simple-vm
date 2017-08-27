#include "vm.h"
#include "print.h"

void printRegisterA() {
  printRegister8(REGISTER_A_X, REGISTER_A_Y + 1, register_A);
}

void printRegisterB() {
  printRegister8(REGISTER_B_X, REGISTER_B_Y + 1, register_B);
}

void printALU() {
  printRegister8(ALU_X, ALU_Y + 1, alu);
}

void printProgramCounter() {
  printRegister4(COUNTER_X, COUNTER_Y + 1, program_counter);
}

void printBus() {
  printRegister8(BUS_X, BUS_Y + 1, bus);
}

void printRam() {
  printRegister4(RAM_X + 9, RAM_Y + 1, memory_address);
  printRegister8(RAM_X + 9, RAM_Y + 2, RAM[memory_address & 0x0F]);
}
