#include "vm.h"
#include "print.h"

void printRegisterA(const CPU *cpu) {
  printRegister8(REGISTER_A_X, REGISTER_A_Y + 1, cpu->register_A);
}

void printRegisterB(const CPU *cpu) {
  printRegister8(REGISTER_B_X, REGISTER_B_Y + 1, cpu->register_B);
}

void printALU(const CPU *cpu) {
  printRegister8(ALU_X, ALU_Y + 1, cpu->alu_output);
}

void printProgramCounter(const CPU *cpu) {
  printRegister4(COUNTER_X, COUNTER_Y + 1, cpu->program_counter);
}

void printBus(const CPU *cpu) {
  printRegister8(BUS_X, BUS_Y + 1, cpu->bus);
}

void printRam(const CPU *cpu, const ram_type RAM) {
  printRegister4(RAM_X + 9, RAM_Y + 1, cpu->memory_address);
  printRegister8(RAM_X + 9, RAM_Y + 2, RAM[cpu->memory_address & 0x0F]);
}
