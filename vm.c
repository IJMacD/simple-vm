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
unsigned char memory_address = 0x0;
unsigned char alu = 0x00;
unsigned char RAM[16] = { 0 };

unsigned char bus;

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

void updateALU() {
  alu = register_A + register_B;
}

void updateDisplay() {
  printRegisterA();
  printRegisterB();
  printALU();
  printProgramCounter();
  printBus();
  printRam();
}

void main() {
  // Create blank console
  hConsole =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);

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

  register_B = 255;

  while(1){
    updateDisplay();

    program_counter++;
    register_A++;
    register_B--;
    updateALU();
    memory_address++;

    Sleep(100);
  }

}
