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
  char output[255];
  DWORD len = sprintf(output, "0x%02X " PRINTF_BINARY_PATTERN_INT4, reg & 0x0F, PRINTF_BYTE_TO_BINARY_INT4(reg));
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacterA(hConsole, output, len, pos, &dwBytesWritten);
}

void printRegister8(int x, int y, unsigned char reg) {
  char output[255];
  DWORD len = sprintf(output, "0x%02X " PRINTF_BINARY_PATTERN_INT8, reg, PRINTF_BYTE_TO_BINARY_INT8(reg));
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacterA(hConsole, output, len, pos, &dwBytesWritten);
}

void printRegister16(int x, int y, unsigned char reg) {
  char output[255];
  DWORD len = sprintf(output, "0x%04X", reg);
  DWORD dwBytesWritten = 0;
  pos.X = x;
  pos.Y = y;
  WriteConsoleOutputCharacterA(hConsole, output, len, pos, &dwBytesWritten);
}

void printLabels() {

  // RegisterA
  pos.X = REGISTER_A_X;
  pos.Y = REGISTER_A_Y;
  const char rega_lbl[] = "Register A";
  WriteConsoleOutputCharacterA(hConsole, rega_lbl, LENGTH(rega_lbl) - 1, pos, &dwBytesWritten);
  pos.X = REGISTER_A_X;
  pos.Y = REGISTER_A_Y + 2;
  const char flag_lbl[] = "Flag";
  WriteConsoleOutputCharacterA(hConsole, flag_lbl, LENGTH(flag_lbl) - 1, pos, &dwBytesWritten);

  // RegisterB
  pos.X = REGISTER_B_X;
  pos.Y = REGISTER_B_Y;
  const char regb_lbl[] = "Register B";
  WriteConsoleOutputCharacterA(hConsole, regb_lbl, LENGTH(regb_lbl) - 1, pos, &dwBytesWritten);

  // RegisterC
  pos.X = REGISTER_C_X;
  pos.Y = REGISTER_C_Y;
  const char regc_lbl[] = "Register C";
  WriteConsoleOutputCharacterA(hConsole, regc_lbl, LENGTH(regc_lbl) - 1, pos, &dwBytesWritten);

  // RegisterTMP
  pos.X = REGISTER_TMP_X;
  pos.Y = REGISTER_TMP_Y;
  const char regtmp_lbl[] = "Register TMP";
  WriteConsoleOutputCharacterA(hConsole, regtmp_lbl, LENGTH(regtmp_lbl) - 1, pos, &dwBytesWritten);

  // ALU
  pos.X = ALU_X;
  pos.Y = ALU_Y;
  const char alu_lbl[] = "ALU";
  WriteConsoleOutputCharacterA(hConsole, alu_lbl, LENGTH(alu_lbl) - 1, pos, &dwBytesWritten);

  // Program Counter
  pos.X = COUNTER_X;
  pos.Y = COUNTER_Y;
  const char counter_lbl[] = "Counter";
  WriteConsoleOutputCharacterA(hConsole, counter_lbl, LENGTH(counter_lbl) - 1, pos, &dwBytesWritten);

  // Bus Indicator
  pos.X = BUS_X;
  pos.Y = BUS_Y;
  const char bus_lbl[] = "Bus";
  WriteConsoleOutputCharacterA(hConsole, bus_lbl, LENGTH(bus_lbl) - 1, pos, &dwBytesWritten);

  // Clock
  pos.X = CLOCK_X;
  pos.Y = CLOCK_Y;
  const char clock_lbl[] = "Clock";
  WriteConsoleOutputCharacterA(hConsole, clock_lbl, LENGTH(clock_lbl) - 1, pos, &dwBytesWritten);

  // RAM
  pos.X = RAM_X;
  pos.Y = RAM_Y;
  const char ram_lbl[] = "RAM";
  WriteConsoleOutputCharacterA(hConsole, ram_lbl, LENGTH(ram_lbl) - 1, pos, &dwBytesWritten);
  pos.X = RAM_X;
  pos.Y = RAM_Y + 1;
  const char rama_lbl[] = "Address";
  WriteConsoleOutputCharacterA(hConsole, rama_lbl, LENGTH(rama_lbl) - 1, pos, &dwBytesWritten);
  pos.X = RAM_X;
  pos.Y = RAM_Y + 2;
  const char ramc_lbl[] = "Contents";
  WriteConsoleOutputCharacterA(hConsole, ramc_lbl, LENGTH(ramc_lbl) - 1, pos, &dwBytesWritten);

  // Output
  pos.X = OUTPUT_X;
  pos.Y = OUTPUT_Y;
  const wchar_t output_lbl[] = L"Output";
  WriteConsoleOutputCharacterW(hConsole, output_lbl, LENGTH(output_lbl) - 1, pos, &dwBytesWritten);
  pos.X = OUTPUT_X+14;
  pos.Y = OUTPUT_Y;
  const wchar_t output_box_top[] = L"\u2554\u2550\u2550\u2550\u2550\u2557";
  WriteConsoleOutputCharacterW(hConsole, output_box_top, LENGTH(output_box_top) - 1, pos, &dwBytesWritten);
  pos.Y = OUTPUT_Y+1;
  const wchar_t output_box_mid[] = L"\u2551    \u2551";
  WriteConsoleOutputCharacterW(hConsole, output_box_mid, LENGTH(output_box_mid) - 1, pos, &dwBytesWritten);
  pos.Y = OUTPUT_Y+2;
  const wchar_t output_box_bot[] = L"\u255a\u2550\u2550\u2550\u2550\u255d";
  WriteConsoleOutputCharacterW(hConsole, output_box_bot, LENGTH(output_box_bot) - 1, pos, &dwBytesWritten);

  // Instruction Register
  pos.X = INSTRUCTION_X;
  pos.Y = INSTRUCTION_Y;
  const char instruction_lbl[] = "Instruction";
  WriteConsoleOutputCharacterA(hConsole, instruction_lbl, LENGTH(instruction_lbl) - 1, pos, &dwBytesWritten);

  // Instruction Decoder
  pos.X = DECODER_X;
  pos.Y = DECODER_Y;
  const char decoder_lbl[] = "Decoder Phase";
  WriteConsoleOutputCharacterA(hConsole, decoder_lbl, LENGTH(decoder_lbl) - 1, pos, &dwBytesWritten);
  pos.X = DECODER_X;
  pos.Y = DECODER_Y + 1;
  const char phase_lbl[] = "0 1 2 3 4 5 6";
  WriteConsoleOutputCharacterA(hConsole, phase_lbl, LENGTH(phase_lbl) - 1, pos, &dwBytesWritten);

  // Control
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y;
  const char control_lbl[] = "Control";
  WriteConsoleOutputCharacterA(hConsole, control_lbl, LENGTH(control_lbl) - 1, pos, &dwBytesWritten);
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y + 1;
  const char line_lbl[] = "HT MI RI RO IO II AI AO EO SU BI OI CE PO JP DR";
  WriteConsoleOutputCharacterA(hConsole, line_lbl, LENGTH(line_lbl) - 1, pos, &dwBytesWritten);

  // Ram Map
  pos.X = RAM_MAP_X + 1;
  pos.Y = RAM_MAP_Y;
  const char ram_map_lbl[] = "RAM Map";
  WriteConsoleOutputCharacterA(hConsole, ram_map_lbl, LENGTH(ram_map_lbl) - 1, pos, &dwBytesWritten);

  // Help text
  CONSOLE_SCREEN_BUFFER_INFO sbInfo;
  GetConsoleScreenBufferInfo(hConsole, &sbInfo);
  pos.X = HELP_X;
  pos.Y = (sbInfo.dwSize.Y < HELP_Y) ? HELP_Y : sbInfo.dwSize.Y - 1;
  const char help_lbl[] = "SPACE - Step   h - Toggle halt   r - Reset   f - Faster   s - Slower  q - Quit";
  WriteConsoleOutputCharacterA(hConsole, help_lbl, LENGTH(help_lbl) - 1, pos, &dwBytesWritten);

  // Bus Graphic
  int y;
  pos.X = BUS_X + 6;
  for(y = BUS_Y + 2; y < CONTROL_Y; y++) {
    pos.Y = y;
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacterW(hConsole, L"\u2551", 1, pos, &dwBytesWritten);
  }
}

void printRegisterA(const CPU *cpu) {
  printRegister8(REGISTER_A_X, REGISTER_A_Y + 1, cpu->register_A);
  char output[8];
  output[0] = (cpu->alu_flags & ALU_FLAG_S) ? 'S' : ' ';
  output[1] = (cpu->alu_flags & ALU_FLAG_Z) ? 'Z' : ' ';
  pos.X = REGISTER_A_X + 5;
  pos.Y = REGISTER_A_Y + 2;
  WriteConsoleOutputCharacterA(hConsole, output, 2, pos, &dwBytesWritten);
}

void printOutput(const CPU *cpu) {
  printRegister8(OUTPUT_X, OUTPUT_Y + 1, cpu->port_3);
  char output[255];
  DWORD len = sprintf(output, "%3d", cpu->port_3);
  DWORD dwBytesWritten = 0;
  pos.X = OUTPUT_X + 16;
  pos.Y = OUTPUT_Y + 1;
  WriteConsoleOutputCharacterA(hConsole, output, len, pos, &dwBytesWritten);
}

void printInstruction(const CPU *cpu) {
  printRegister8(INSTRUCTION_X, INSTRUCTION_Y + 1, cpu->register_I);
  char label[10] = "          ";
  const char *mne = mne_labels[cpu->register_I];
  if (mne != NULL) {
    memcpy(label, mne, strlen(mne));
  }

  pos.X = INSTRUCTION_X + 5;
  pos.Y = INSTRUCTION_Y + 2;
  DWORD dwBytesWritten;
  WriteConsoleOutputCharacterA(hConsole, label, sizeof(label), pos, &dwBytesWritten);
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
  WriteConsoleOutputCharacterW(hConsole, output, PHASE_COUNT * 2, pos, &dwBytesWritten);
}

void printControl(const CPU *cpu) {
  pos.X = CONTROL_X;
  pos.Y = CONTROL_Y + 2;

  wchar_t output[CONTROL_LINES * 3];
  int i, offset = 0;
  for(i = 0; i < CONTROL_LINES; i++) {
    unsigned int bit = 1 << (31 - i);
    output[offset++] = cpu->control_word & bit ? 0x2550 : ' '; // '─' U+2550 Box Drawing Horizontal Double Bar
    output[offset++] = cpu->control_word & bit ? 0x2550 : ' ';
    output[offset++] = ' ';
  }

  DWORD dwBytesWritten;
  WriteConsoleOutputCharacterW(hConsole, output, CONTROL_LINES * 3, pos, &dwBytesWritten);
}

void printClock(const CPU *cpu) {
  pos.X = CLOCK_X;
  pos.Y = CLOCK_Y + 1;
  if (cpu->halt) {
    const char clock_lbl[] = "HALT   "; // Extra spaces to cover up "RUNNING"
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacterA(hConsole, clock_lbl, LENGTH(clock_lbl) - 1, pos, &dwBytesWritten);
  } else {
    const char clock_lbl[] = "RUNNING";
    DWORD dwBytesWritten;
    WriteConsoleOutputCharacterA(hConsole, clock_lbl, LENGTH(clock_lbl) - 1, pos, &dwBytesWritten);
  }
}

void printRamMap(const CPU *cpu, const ram_type RAM) {
  pos.X = RAM_MAP_X;

  DWORD dwBytesWritten;
  wchar_t output[16] = { 0 };
  int i, offset;
  for(i = 0; i < RAM_MAP_SIZE; i++) {
    offset = 0;
    output[offset++] = cpu->memory_address == i ? 0x25BA : ' '; // U+25BA BLACK RIGHT-POINTING POINTER
    wsprintfW(&output[offset], L"0x%04X 0x%02X", i, RAM[i]);
    offset += 11;
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
  unsigned int control_word = cpu->control_word;

  // Memory In
  pos.X = BUS_X - 2;
  pos.Y = RAM_Y + 1;
  output = (control_word & MI) ? sarrow_l : spaces;
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // RAM In/Out
  pos.X = BUS_X - 2;
  pos.Y = RAM_Y + 2;
  output = (control_word & RI) ? darrow_l : ((control_word & RO) ? darrow_r : spaces);
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Instruction In
  pos.X = BUS_X - 2;
  pos.Y = INSTRUCTION_Y + 1;
  output = (control_word & II) ? darrow_l : spaces;
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Counter In/Out
  pos.X = BUS_X - 2;
  pos.Y = COUNTER_Y + 1;
  output = (control_word & PO) ? sarrow_r : ((control_word & JP) ? sarrow_l : spaces);
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Register A In/Out
  pos.X = BUS_X + 7;
  pos.Y = REGISTER_A_Y + 1;
  output = (control_word & AO) ? darrow_l : ((control_word & AI) ? darrow_r : spaces);
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // ALU Out
  pos.X = BUS_X + 7;
  pos.Y = ALU_Y + 1;
  output = (control_word & EO) ? darrow_l : spaces;
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Register B In/Out
  pos.X = BUS_X + 7;
  pos.Y = REGISTER_B_Y + 1;
  output = (control_word & BO) ? darrow_l : ((control_word & BI) ? darrow_r : spaces);
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Register C In/Out
  pos.X = BUS_X + 7;
  pos.Y = REGISTER_C_Y + 1;
  output = (control_word & CO) ? darrow_l : ((control_word & CI) ? darrow_r : spaces);
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Register TMP In
  pos.X = BUS_X + 7;
  pos.Y = REGISTER_TMP_Y + 1;
  output = (control_word & TI) ? darrow_r : spaces;
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);

  // Output In
  pos.X = BUS_X + 7;
  pos.Y = OUTPUT_Y + 1;
  output = (control_word & O3) ? darrow_r : spaces;
  WriteConsoleOutputCharacterW(hConsole, output, 8, pos, &dwBytesWritten);
}
