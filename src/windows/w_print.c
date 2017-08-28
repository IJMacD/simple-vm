#include <windows.h>
#include <stdio.h>

#include "../vm.h"
#include "../print.h"

/*   windows/vm.c   */
extern void *hConsole;

// Lazy temps, to save always redeclaring
COORD pos;
DWORD dwBytesWritten = 0;

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
  pos.X = COUNTER_X;
  pos.Y = COUNTER_Y;
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
  pos.X = OUTPUT_X+8;
  pos.Y = OUTPUT_Y+2;
  const char output_box_top[] = "\xc9\xcd\xcd\xcd\xcd\xbb";
  WriteConsoleOutputCharacter(hConsole, output_box_top, sizeof(output_box_top) - 1, pos, &dwBytesWritten);
  pos.Y = OUTPUT_Y+3;
  const char output_box_mid[] = "\xba    \xba";
  WriteConsoleOutputCharacter(hConsole, output_box_mid, sizeof(output_box_mid) - 1, pos, &dwBytesWritten);
  pos.Y = OUTPUT_Y+4;
  const char output_box_bot[] = "\xc8\xcd\xcd\xcd\xcd\xbc";
  WriteConsoleOutputCharacter(hConsole, output_box_bot, sizeof(output_box_bot) - 1, pos, &dwBytesWritten);

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

  // Ram Map
  pos.X = RAM_MAP_X + 1;
  pos.Y = RAM_MAP_Y;
  const char ram_map_lbl[] = "RAM Map";
  WriteConsoleOutputCharacter(hConsole, ram_map_lbl, sizeof(ram_map_lbl) - 1, pos, &dwBytesWritten);

  // Help text
  CONSOLE_SCREEN_BUFFER_INFO sbInfo;
  GetConsoleScreenBufferInfo(hConsole, &sbInfo);
  pos.X = HELP_X;
  pos.Y = sbInfo.dwSize.Y - 1;
  const char help_lbl[] = "SPACE - Step   a - Toggle halt   r - Reset   f - Faster   s - Slower  q - Quit";
  WriteConsoleOutputCharacter(hConsole, help_lbl, sizeof(help_lbl) - 1, pos, &dwBytesWritten);

  // Bus Graphic
  int y;
  pos.X = BUS_X + 6;
  for(y = BUS_Y + 2; y < CONTROL_Y; y++) {
    pos.Y = y;
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacter(hConsole, "\xba", 1, pos, &dwBytesWritten);
  }
}

void printOutput() {
  printRegister8(OUTPUT_X, OUTPUT_Y + 1, register_O);
  char output[255];
  DWORD len = sprintf(output, "%3d", register_O);
  DWORD dwBytesWritten = 0;
  pos.X = OUTPUT_X + 10;
  pos.Y = OUTPUT_Y + 3;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printInstruction() {
  printRegister4(INSTRUCTION_X, INSTRUCTION_Y + 1, register_I >> 4);
  printRegister4(INSTRUCTION_X + 10, INSTRUCTION_Y + 1, register_I);
  const char inst_lbl[] = "NOPLDAADDSUBSTALDIJMP                     OUTHLT";
  pos.X = INSTRUCTION_X + 6;
  pos.Y = INSTRUCTION_Y + 2;
  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, &inst_lbl[(register_I >> 4) * 3], 3, pos, &dwBytesWritten);
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
    output[offset++] = decoder_output & bit ? '\xcd' : ' '; // '─' U+2500 DOS (code page 437) character: C4
    output[offset++] = decoder_output & bit ? '\xcd' : ' ';
    output[offset++] = ' ';
  }

  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, output, CONTROL_LINES * 3, pos, &dwBytesWritten);
}

void printClock() {
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

void printRamMap() {
  pos.X = RAM_MAP_X;

  DWORD dwBytesWritten;
  char output[9];
  int i, offset;
  for(i = 0; i < 16; i++) {
    offset = 0;
    output[offset++] = memory_address == i ? '>' : ' ';
    sprintf(&output[offset], "%02X 0x%02X", i, RAM[i]);

    pos.Y = RAM_MAP_Y + i + 1;
    WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);
  }
}

void printBusGraphic() {
  const char sarrow_l[] = "\x11\xc4\xc4\xc4\xc4\xc4\xc4\xc4";
  const char sarrow_r[] = "\xc4\xc4\xc4\xc4\xc4\xc4\xc4\x10";
  const char darrow_l[] = "\x11\xcd\xcd\xcd\xcd\xcd\xcd\xcd";
  const char darrow_r[] = "\xcd\xcd\xcd\xcd\xcd\xcd\xcd\x10";
  const char spaces[]   = "        ";

  const char *output;

  // Memory In
  pos.X = BUS_X - 2;
  pos.Y = RAM_Y + 1;
  output = (decoder_output & MI) ? sarrow_l : spaces;
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // RAM In/Out
  pos.X = BUS_X - 2;
  pos.Y = RAM_Y + 2;
  output = (decoder_output & RI) ? darrow_l : ((decoder_output & RO) ? darrow_r : spaces);
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // Instruction In/Out
  pos.X = BUS_X - 2;
  pos.Y = INSTRUCTION_Y + 1;
  output = (decoder_output & II) ? darrow_l : ((decoder_output & IO) ? sarrow_r : spaces);
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // Counter In/Out
  pos.X = BUS_X + 7;
  pos.Y = COUNTER_Y + 1;
  output = (decoder_output & CO) ? sarrow_l : ((decoder_output & JP) ? sarrow_r : spaces);
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // Register A In/Out
  pos.X = BUS_X + 7;
  pos.Y = REGISTER_A_Y + 1;
  output = (decoder_output & AO) ? darrow_l : ((decoder_output & AI) ? darrow_r : spaces);
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // ALU Out
  pos.X = BUS_X + 7;
  pos.Y = ALU_Y + 1;
  output = (decoder_output & EO) ? darrow_l : spaces;
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // Register B In
  pos.X = BUS_X + 7;
  pos.Y = REGISTER_B_Y + 1;
  // output = (decoder_output & BO) ? darrow_l : ((decoder_output & BI) ? darrow_r : spaces);
  output = (decoder_output & BI) ? darrow_r : spaces;
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);

  // Output In
  pos.X = BUS_X + 7;
  pos.Y = OUTPUT_Y + 1;
  output = (decoder_output & OI) ? darrow_r : spaces;
  WriteConsoleOutputCharacter(hConsole, output, 8, pos, &dwBytesWritten);
}
