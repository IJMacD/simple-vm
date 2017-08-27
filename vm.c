#include <windows.h>
#include <stdio.h>

#include "ben.h"

#define REGISTER_A_X  55
#define REGISTER_A_Y   4
#define REGISTER_B_X  55
#define REGISTER_B_Y  10
#define ALU_X         57
#define ALU_Y          7
#define PROGRAM_COUNTER_X         55
#define PROGRAM_COUNTER_Y          1
#define BUS_X         33
#define BUS_Y          0
#define CLOCK_X        2
#define CLOCK_Y        1
#define RAM_X          2
#define RAM_Y          4
#define OUTPUT_X      55
#define OUTPUT_Y      13
#define INSTRUCTION_X  2
#define INSTRUCTION_Y  8
#define DECODER_X      2
#define DECODER_Y     11
#define CONTROL_X      8
#define CONTROL_Y     18

#define PHASE_COUNT 5
#define CONTROL_LINES 15

#define PRINTF_BINARY_PATTERN_INT4 "%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT4(i)    \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')

    #define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
    #define PRINTF_BYTE_TO_BINARY_INT8(i)    \
        (((i) & 0x80ll) ? '1' : '0'), \
        (((i) & 0x40ll) ? '1' : '0'), \
        (((i) & 0x20ll) ? '1' : '0'), \
        (((i) & 0x10ll) ? '1' : '0'), \
        (((i) & 0x08ll) ? '1' : '0'), \
        (((i) & 0x04ll) ? '1' : '0'), \
        (((i) & 0x02ll) ? '1' : '0'), \
        (((i) & 0x01ll) ? '1' : '0')

unsigned char register_A = 0x00;
unsigned char register_B = 0x00;
unsigned char register_I = 0x00;         // Instruction register
unsigned char register_O = 0x00;         // Output register
unsigned char program_counter = 0x00;
unsigned char memory_address = 0x00;
unsigned char alu = 0x00;
unsigned char RAM[16] = {
  LDA | 0x0E,
  ADD | 0x0F,
  OPT,
  HLT,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  28,
  14
};
unsigned char decoder_phase = 0x00;
unsigned char bus;
unsigned short decoder_output = 0x00;
unsigned char halt = 0x00;

void *hConsole;
COORD pos;

void printRegister4(int x, int y, unsigned char reg) {
  char output[255];
  DWORD len = sprintf(output, "0x%02X " PRINTF_BINARY_PATTERN_INT4, reg & 0x0F, PRINTF_BYTE_TO_BINARY_INT4(reg));
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printRegister8(int x, int y, unsigned char reg) {
  char output[255];
  DWORD len = sprintf(output, "0x%02X " PRINTF_BINARY_PATTERN_INT8, reg, PRINTF_BYTE_TO_BINARY_INT8(reg));
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printLabels() {
  char output[255];
  DWORD len;
  DWORD dwBytesWritten = 0;

  // RegisterA
  pos.X = REGISTER_A_X;
  pos.Y = REGISTER_A_Y;
  const char rega_lbl[] = "Register A";
  WriteConsoleOutputCharacter(hConsole, rega_lbl, sizeof(rega_lbl) - 1, pos, &dwBytesWritten);

  // RegisterB
  pos.X = REGISTER_B_X;
  pos.Y = REGISTER_B_Y;
  const char regb_lbl[] = "Register B";
  WriteConsoleOutputCharacter(hConsole, regb_lbl, sizeof(regb_lbl) - 1, pos, &dwBytesWritten);

  // ALU
  pos.X = ALU_X;
  pos.Y = ALU_Y;
  const char alu_lbl[] = "ALU";
  WriteConsoleOutputCharacter(hConsole, alu_lbl, sizeof(alu_lbl) - 1, pos, &dwBytesWritten);

  // Program Counter
  pos.X = PROGRAM_COUNTER_X;
  pos.Y = PROGRAM_COUNTER_Y;
  const char counter_lbl[] = "Counter";
  WriteConsoleOutputCharacter(hConsole, counter_lbl, sizeof(counter_lbl) - 1, pos, &dwBytesWritten);

  // Bus Indicator
  pos.X = BUS_X;
  pos.Y = BUS_Y;
  const char bus_lbl[] = "Bus";
  WriteConsoleOutputCharacter(hConsole, bus_lbl, sizeof(bus_lbl) - 1, pos, &dwBytesWritten);

  // Clock
  pos.X = CLOCK_X;
  pos.Y = CLOCK_Y;
  const char clock_lbl[] = "Clock";
  WriteConsoleOutputCharacter(hConsole, clock_lbl, sizeof(clock_lbl) - 1, pos, &dwBytesWritten);

  // RAM
  pos.X = RAM_X;
  pos.Y = RAM_Y;
  const char ram_lbl[] = "RAM";
  WriteConsoleOutputCharacter(hConsole, ram_lbl, sizeof(ram_lbl) - 1, pos, &dwBytesWritten);
  pos.X = RAM_X;
  pos.Y = RAM_Y + 1;
  const char rama_lbl[] = "Address";
  WriteConsoleOutputCharacter(hConsole, rama_lbl, sizeof(rama_lbl) - 1, pos, &dwBytesWritten);
  pos.X = RAM_X;
  pos.Y = RAM_Y + 2;
  const char ramc_lbl[] = "Contents";
  WriteConsoleOutputCharacter(hConsole, ramc_lbl, sizeof(ramc_lbl) - 1, pos, &dwBytesWritten);

  // Output
  pos.X = OUTPUT_X;
  pos.Y = OUTPUT_Y;
  const char output_lbl[] = "Output";
  WriteConsoleOutputCharacter(hConsole, output_lbl, sizeof(output_lbl) - 1, pos, &dwBytesWritten);

  // Instruction Register
  pos.X = INSTRUCTION_X;
  pos.Y = INSTRUCTION_Y;
  const char instruction_lbl[] = "Instruction";
  WriteConsoleOutputCharacter(hConsole, instruction_lbl, sizeof(instruction_lbl) - 1, pos, &dwBytesWritten);

  // Instruction Decoder
  pos.X = DECODER_X;
  pos.Y = DECODER_Y;
  const char decoder_lbl[] = "Decoder Phase";
  WriteConsoleOutputCharacter(hConsole, decoder_lbl, sizeof(decoder_lbl) - 1, pos, &dwBytesWritten);
  pos.X = DECODER_X;
  pos.Y = DECODER_Y + 1;
  const char phase_lbl[] = "0 1 2 3 4";
  WriteConsoleOutputCharacter(hConsole, phase_lbl, sizeof(phase_lbl) - 1, pos, &dwBytesWritten);

  // Control
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y;
  const char control_lbl[] = "Control";
  WriteConsoleOutputCharacter(hConsole, control_lbl, sizeof(control_lbl) - 1, pos, &dwBytesWritten);
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y + 1;
  const char line_lbl[] = "HT MI RI RO IO II AI AO EO SU BI OI CE CO JP";
  WriteConsoleOutputCharacter(hConsole, line_lbl, sizeof(line_lbl) - 1, pos, &dwBytesWritten);
}

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
  printRegister4(PROGRAM_COUNTER_X, PROGRAM_COUNTER_Y + 1, program_counter);
}

void printBus() {
  printRegister8(BUS_X, BUS_Y + 1, bus);
}

void printRam() {
  printRegister4(RAM_X + 9, RAM_Y + 1, memory_address);
  printRegister8(RAM_X + 9, RAM_Y + 2, RAM[memory_address & 0x0F]);
}

void printOutput() {
  printRegister8(OUTPUT_X, OUTPUT_Y + 1, register_O);
  char output[255];
  DWORD len = sprintf(output, "%8d", register_O);
  DWORD dwBytesWritten = 0;
  pos.X = OUTPUT_X + 5;
  pos.Y = OUTPUT_Y + 2;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printInstruction() {
  printRegister4(INSTRUCTION_X, INSTRUCTION_Y + 1, register_I >> 4);
  printRegister4(INSTRUCTION_X + 10, INSTRUCTION_Y + 1, register_I);
}

void printDecoder() {
  pos.X = DECODER_X;
  pos.Y = DECODER_Y + 2;

  int phase = decoder_phase & 0x07;
  char output[PHASE_COUNT * 2];
  int i, offset = 0;
  for(i = 0; i < PHASE_COUNT + 1; i++) {
    output[offset++] = phase == i ? '^' : ' ';
    output[offset++] = ' ';
  }

  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, output, PHASE_COUNT * 2, pos, &dwBytesWritten);
}

void printControl() {
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y + 2;

  char output[CONTROL_LINES * 3];
  int i, offset = 0;
  for(i = 0; i < CONTROL_LINES; i++) {
    unsigned short bit = 1 << (15 - i);
    output[offset++] = decoder_output & bit ? '—' : ' ';
    output[offset++] = decoder_output & bit ? '—' : ' ';
    output[offset++] = ' ';
  }

  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, output, CONTROL_LINES * 3, pos, &dwBytesWritten);
}

printClock() {
  pos.X = CLOCK_X;
  pos.Y = CLOCK_Y + 1;
  if (halt) {
    const char clock_lbl[] = "HALT   "; // Extra spaces to cover up "RUNNING"
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacter(hConsole, clock_lbl, sizeof(clock_lbl) - 1, pos, &dwBytesWritten);
  } else {
    const char clock_lbl[] = "RUNNING";
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacter(hConsole, clock_lbl, sizeof(clock_lbl) - 1, pos, &dwBytesWritten);
  }
}

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

void main() {
  // Create blank console
  hConsole =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  SetConsoleOutputCP(1252); // Windows-1252 ANSI Latin 1
  // SetConsoleOutputCP(65001);  // UTF-8

  // Move Cursor out of the way and hide
  {
    COORD new_pos = {79, 0};
    SetConsoleCursorPosition(hConsole, new_pos);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    // info.dwSize = 25;
    info.bVisible = info.bVisible ? FALSE : TRUE;
    SetConsoleCursorInfo(hConsole, &info);
  }

  printLabels();

  step();

  while(1){

    if(halt) {
      if(_kbhit()) {
        char c = _getch();
        if(c == ' ') step();
        else if(c == 'r') reset();
        else if(c == 'a') halt = 0;
      }
      Sleep(100);
    } else {
      step();
      Sleep(1000);
    }
  }

}
