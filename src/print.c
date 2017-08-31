#include "vm.h"
#include "print.h"

void printRegisterB(const CPU *cpu) {
  printRegister8(REGISTER_B_X, REGISTER_B_Y + 1, cpu->register_B);
}

void printRegisterC(const CPU *cpu) {
  printRegister8(REGISTER_C_X, REGISTER_C_Y + 1, cpu->register_C);
}

void printRegisterTMP(const CPU *cpu) {
  printRegister8(REGISTER_TMP_X, REGISTER_TMP_Y + 1, cpu->register_TMP);
}

void printALU(const CPU *cpu) {
  printRegister8(ALU_X, ALU_Y + 1, cpu->alu_output);
}

void printProgramCounter(const CPU *cpu) {
  printRegister16(COUNTER_X, COUNTER_Y + 1, cpu->program_counter);
}

void printBus(const CPU *cpu) {
  printRegister16(BUS_X, BUS_Y + 1, cpu->bus);
}

void printRam(const CPU *cpu, const ram_type RAM) {
  printRegister16(RAM_X + 9, RAM_Y + 1, cpu->memory_address);
  printRegister8(RAM_X + 9, RAM_Y + 2, RAM[cpu->memory_address & 0xFFFF]);
}

void updateDisplay(const CPU *cpu, const ram_type RAM) {
  printRegisterA(cpu);
  printRegisterB(cpu);
  printRegisterC(cpu);
  printRegisterTMP(cpu);
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
