#include <windows.h>
#include <stdio.h>

#include "../vm.h"
#include "../print.h"

#define LENGTH(x) sizeof(x) / sizeof(x[0])

/*   windows/vm.c   */
extern void *hConsole;

// Lazy temps, to save always redeclaring
COORD pos;
DWORD dwBytesWritten = 0;

void printRegister4(int x, int y, unsigned char reg) {
  wchar_t output[255];
  DWORD len = wsprintf(output, L"0x%02X " PRINTF_BINARY_PATTERN_INT4, reg & 0x0F, PRINTF_BYTE_TO_BINARY_INT4(reg));
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printRegister8(int x, int y, unsigned char reg) {
  wchar_t output[255];
  DWORD len = wsprintf(output, L"0x%02X " PRINTF_BINARY_PATTERN_INT8, reg, PRINTF_BYTE_TO_BINARY_INT8(reg));
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printLabels() {

  // RegisterA
  pos.X = REGISTER_A_X;
  pos.Y = REGISTER_A_Y;
  const wchar_t rega_lbl[] = L"Register A";
  WriteConsoleOutputCharacter(hConsole, rega_lbl, LENGTH(rega_lbl) - 1, pos, &dwBytesWritten);

  // RegisterB
  pos.X = REGISTER_B_X;
  pos.Y = REGISTER_B_Y;
  const wchar_t regb_lbl[] = L"Register B";
  WriteConsoleOutputCharacter(hConsole, regb_lbl, LENGTH(regb_lbl) - 1, pos, &dwBytesWritten);

  // ALU
  pos.X = ALU_X;
  pos.Y = ALU_Y;
  const wchar_t alu_lbl[] = L"ALU";
  WriteConsoleOutputCharacter(hConsole, alu_lbl, LENGTH(alu_lbl) - 1, pos, &dwBytesWritten);

  // Program Counter
  pos.X = COUNTER_X;
  pos.Y = COUNTER_Y;
  const wchar_t counter_lbl[] = L"Counter";
  WriteConsoleOutputCharacter(hConsole, counter_lbl, LENGTH(counter_lbl) - 1, pos, &dwBytesWritten);

  // Bus Indicator
  pos.X = BUS_X;
  pos.Y = BUS_Y;
  const wchar_t bus_lbl[] = L"Bus";
  WriteConsoleOutputCharacter(hConsole, bus_lbl, LENGTH(bus_lbl) - 1, pos, &dwBytesWritten);

  // Clock
  pos.X = CLOCK_X;
  pos.Y = CLOCK_Y;
  const wchar_t clock_lbl[] = L"Clock";
  WriteConsoleOutputCharacter(hConsole, clock_lbl, LENGTH(clock_lbl) - 1, pos, &dwBytesWritten);

  // RAM
  pos.X = RAM_X;
  pos.Y = RAM_Y;
  const wchar_t ram_lbl[] = L"RAM";
  WriteConsoleOutputCharacter(hConsole, ram_lbl, LENGTH(ram_lbl) - 1, pos, &dwBytesWritten);
  pos.X = RAM_X;
  pos.Y = RAM_Y + 1;
  const wchar_t rama_lbl[] = L"Address";
  WriteConsoleOutputCharacter(hConsole, rama_lbl, LENGTH(rama_lbl) - 1, pos, &dwBytesWritten);
  pos.X = RAM_X;
  pos.Y = RAM_Y + 2;
  const wchar_t ramc_lbl[] = L"Contents";
  WriteConsoleOutputCharacter(hConsole, ramc_lbl, LENGTH(ramc_lbl) - 1, pos, &dwBytesWritten);

  // Output
  pos.X = OUTPUT_X;
  pos.Y = OUTPUT_Y;
  const wchar_t output_lbl[] = L"Output";
  WriteConsoleOutputCharacter(hConsole, output_lbl, LENGTH(output_lbl) - 1, pos, &dwBytesWritten);
  pos.X = OUTPUT_X+8;
  pos.Y = OUTPUT_Y+2;
  const wchar_t output_box_top[] = L"\u2554\u2550\u2550\u2550\u2550\u2557";
  WriteConsoleOutputCharacter(hConsole, output_box_top, LENGTH(output_box_top) - 1, pos, &dwBytesWritten);
  pos.Y = OUTPUT_Y+3;
  const wchar_t output_box_mid[] = L"\u2551    \u2551";
  WriteConsoleOutputCharacter(hConsole, output_box_mid, LENGTH(output_box_mid) - 1, pos, &dwBytesWritten);
  pos.Y = OUTPUT_Y+4;
  const wchar_t output_box_bot[] = L"\u255a\u2550\u2550\u2550\u2550\u255d";
  WriteConsoleOutputCharacter(hConsole, output_box_bot, LENGTH(output_box_bot) - 1, pos, &dwBytesWritten);

  // Instruction Register
  pos.X = INSTRUCTION_X;
  pos.Y = INSTRUCTION_Y;
  const wchar_t instruction_lbl[] = L"Instruction";
  WriteConsoleOutputCharacter(hConsole, instruction_lbl, LENGTH(instruction_lbl) - 1, pos, &dwBytesWritten);

  // Instruction Decoder
  pos.X = DECODER_X;
  pos.Y = DECODER_Y;
  const wchar_t decoder_lbl[] = L"Decoder Phase";
  WriteConsoleOutputCharacter(hConsole, decoder_lbl, LENGTH(decoder_lbl) - 1, pos, &dwBytesWritten);
  pos.X = DECODER_X;
  pos.Y = DECODER_Y + 1;
  const wchar_t phase_lbl[] = L"0 1 2 3 4";
  WriteConsoleOutputCharacter(hConsole, phase_lbl, LENGTH(phase_lbl) - 1, pos, &dwBytesWritten);

  // Control
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y;
  const wchar_t control_lbl[] = L"Control";
  WriteConsoleOutputCharacter(hConsole, control_lbl, LENGTH(control_lbl) - 1, pos, &dwBytesWritten);
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y + 1;
  const wchar_t line_lbl[] = L"HT MI RI RO IO II AI AO EO SU BI OI CE CO JP";
  WriteConsoleOutputCharacter(hConsole, line_lbl, LENGTH(line_lbl) - 1, pos, &dwBytesWritten);

  // Ram Map
  pos.X = RAM_MAP_X + 1;
  pos.Y = RAM_MAP_Y;
  const wchar_t ram_map_lbl[] = L"RAM Map";
  WriteConsoleOutputCharacter(hConsole, ram_map_lbl, LENGTH(ram_map_lbl) - 1, pos, &dwBytesWritten);

  // Help text
  CONSOLE_SCREEN_BUFFER_INFO sbInfo;
  GetConsoleScreenBufferInfo(hConsole, &sbInfo);
  pos.X = HELP_X;
  pos.Y = sbInfo.dwSize.Y - 1;
  const wchar_t help_lbl[] = L"SPACE - Step   h - Toggle halt   r - Reset   f - Faster   s - Slower  q - Quit";
  WriteConsoleOutputCharacter(hConsole, help_lbl, LENGTH(help_lbl) - 1, pos, &dwBytesWritten);

  // Bus Graphic
  int y;
  pos.X = BUS_X + 6;
  for(y = BUS_Y + 2; y < CONTROL_Y; y++) {
    pos.Y = y;
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacter(hConsole, L"\u2551", 1, pos, &dwBytesWritten);
  }
}

void printOutput(const CPU *cpu) {
  printRegister8(OUTPUT_X, OUTPUT_Y + 1, cpu->register_O);
  wchar_t output[255];
  DWORD len = wsprintf(output, L"%3d", cpu->register_O);
  DWORD dwBytesWritten = 0;
  pos.X = OUTPUT_X + 10;
  pos.Y = OUTPUT_Y + 3;
  WriteConsoleOutputCharacter(hConsole, output, len, pos, &dwBytesWritten);
}

void printInstruction(const CPU *cpu) {
  printRegister4(INSTRUCTION_X, INSTRUCTION_Y + 1, cpu->register_I >> 4);
  printRegister4(INSTRUCTION_X + 10, INSTRUCTION_Y + 1, cpu->register_I);
  const wchar_t inst_lbl[] = L"NOPLDAADDSUBSTALDIJMP                     OUTHLT";
  pos.X = INSTRUCTION_X + 6;
  pos.Y = INSTRUCTION_Y + 2;
  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, &inst_lbl[(cpu->register_I >> 4) * 3], 3, pos, &dwBytesWritten);
}

void printDecoder(const CPU *cpu) {
  pos.X = DECODER_X;
  pos.Y = DECODER_Y + 2;

  int phase = cpu->decoder_phase & 0x07;
  wchar_t output[PHASE_COUNT * 2];
  int i, offset = 0;
  for(i = 0; i < PHASE_COUNT + 1; i++) {
    output[offset++] = phase == i ? 0x25B2 : ' '; // BLACK UP-POINTING TRIANGLE
    output[offset++] = ' ';
  }

  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, output, PHASE_COUNT * 2, pos, &dwBytesWritten);
}

void printControl(const CPU *cpu) {
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y + 2;

  wchar_t output[CONTROL_LINES * 3];
  int i, offset = 0;
  for(i = 0; i < CONTROL_LINES; i++) {
    unsigned short bit = 1 << (15 - i);
    output[offset++] = cpu->decoder_output & bit ? 0x2550 : ' '; // '─' U+2550 Box Drawing Horizontal Double Bar
    output[offset++] = cpu->decoder_output & bit ? 0x2550 : ' ';
    output[offset++] = ' ';
  }

  DWORD dwBytesWritten;
  WriteConsoleOutputCharacter(hConsole, output, CONTROL_LINES * 3, pos, &dwBytesWritten);
}

void printClock(const CPU *cpu) {
  pos.X = CLOCK_X;
  pos.Y = CLOCK_Y + 1;
  if (cpu->halt) {
    const wchar_t clock_lbl[] = L"HALT   "; // Extra spaces to cover up "RUNNING"
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacter(hConsole, clock_lbl, LENGTH(clock_lbl) - 1, pos, &dwBytesWritten);
  } else {
    const wchar_t clock_lbl[] = L"RUNNING";
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacter(hConsole, clock_lbl, LENGTH(clock_lbl) - 1, pos, &dwBytesWritten);
  }
}

void printRamMap(const CPU *cpu, const ram_type RAM) {
  pos.X = RAM_MAP_X;

  DWORD dwBytesWritten;
  wchar_t output[12] = { 0 };
  int i, offset;
  for(i = 0; i < 16; i++) {
    offset = 0;
    output[offset++] = cpu->memory_address == i ? 0x25BA : ' '; // U+25BA BLACK RIGHT-POINTING POINTER
    wsprintfW(&output[offset], L"%02X 0x%02X", i, RAM[i]);
    offset += 7;
    output[offset++] = cpu->program_counter == i ? 0x25C4 : ' '; // U+25C4 BLACK LEFT-POINTING POINTER

    pos.Y = RAM_MAP_Y + i + 1;
    WriteConsoleOutputCharacterW(hConsole, output, offset, pos, &dwBytesWritten);
  }
}

void printBusGraphic(const CPU *cpu) {
  const wchar_t sarrow_l[] = L"\u25C4\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
  const wchar_t sarrow_r[] = L"\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u25BA";
  const wchar_t darrow_l[] = L"\u25C4\u2550\u2550\u2550\u2550\u2550\u2550\u2550";
  const wchar_t darrow_r[] = L"\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u25BA";
  const wchar_t spaces[]   = L"        ";

  const wchar_t *output;
  unsigned short decoder_output = cpu->decoder_output;

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
