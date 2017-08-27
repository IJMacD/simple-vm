#include <windows.h>
#include <stdio.h>

#include "ben.h"

#define REGISTER_A_X  0
#define REGISTER_A_Y  0
#define REGISTER_B_X  0
#define REGISTER_B_Y  3
#define ALU_X  0
#define ALU_Y  6

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

void printRegister(int x, int y, unsigned char reg) {
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
  WriteConsoleOutputCharacter(hConsole, rega_lbl, sizeof(rega_lbl), pos, &dwBytesWritten);

  // RegisterB
  pos.X = REGISTER_B_X;
  pos.Y = REGISTER_B_Y;
  const char regb_lbl[] = "Register B";
  WriteConsoleOutputCharacter(hConsole, regb_lbl, sizeof(regb_lbl), pos, &dwBytesWritten);

  // ALU
  pos.X = ALU_X;
  pos.Y = ALU_Y;
  const char alu_lbl[] = "ALU";
  WriteConsoleOutputCharacter(hConsole, alu_lbl, sizeof(alu_lbl), pos, &dwBytesWritten);
}

void printRegisterA() {
  printRegister(REGISTER_A_X, REGISTER_A_Y + 1, register_A);
}

void printRegisterB() {
  printRegister(REGISTER_B_X, REGISTER_B_Y + 1, register_B);
}

void printALU() {
  printRegister(ALU_X, ALU_Y + 1, alu);
}

void updateALU() {
  alu = register_A + register_B;
}

void main() {
  hConsole =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  COORD new_pos = {79, 0};
  SetConsoleCursorPosition(hConsole, new_pos);
  CONSOLE_CURSOR_INFO info;
  GetConsoleCursorInfo(hConsole, &info);
  // info.dwSize = 25;
  info.bVisible = info.bVisible ? FALSE : TRUE;
  SetConsoleCursorInfo(hConsole, &info);

  printLabels();

  register_B = 255;

  int i = 255;
  while(i--){
    printRegisterA();
    printRegisterB();
    printALU();

    register_A++;
    register_B--;
    updateALU();

    Sleep(100);
  }

}
