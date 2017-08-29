#include <windows.h>

#include "../vm.h"

void *hConsole;

int main() {
  // Create blank console
  hConsole =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  // SetConsoleOutputCP(437); // DOS
  // SetConsoleOutputCP(1252); // Windows-1252 ANSI Latin 1
  // SetConsoleOutputCP(65001);  // UTF-8

  // Move Cursor out of the way and hide
  {
    COORD new_pos = {79, 0};
    SetConsoleCursorPosition(hConsole, new_pos);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hConsole, &info);
    // info.dwSize = 25;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
  }

  CPU cpu = {
    .register_A = 0x00,
    .register_B = 0x00,
    .register_I = 0x00,         // Instruction register
    .register_O = 0x00,         // Output register
    .program_counter = 0x00,
    .memory_address = 0x00,
    .alu = 0x00,
    .decoder_phase = 0x00,
    .decoder_output = 0x00,
    .halt = 0x00
  };

  ram_type prog1 = PRGRM_1;
  ram_type prog2 = PRGRM_2;
  ram_type prog3 = PRGRM_3;
  ram_type *RAM = &prog3;
  unsigned int sleep_delay = DEFAULT_SLEEP;

  printLabels();

  // Kick-off first render
  render(&cpu, *RAM);

  Sleep(sleep_delay);

  while(1){

    if(_kbhit()) {
      char c = _getch();
      if(c == ' ') step(&cpu, *RAM);
      else if(c == 'r') {
        reset(&cpu);
        // Render will:
        // * decode instruction;
        // * update relevant registers (execute);
        // * update display
        render(&cpu, *RAM);
      }
      else if(c == 'h') {
        cpu.halt = cpu.halt ? 0 : 1;
        printClock(&cpu);
      } else if (c == 'f') {
        sleep_delay /= 2;
        if (sleep_delay < 10) sleep_delay = 10;
      } else if (c == 's') {
        sleep_delay *= 2;
      } else if (c == '1') {
        RAM = &prog1;
        render(&cpu, *RAM);
      } else if (c == '2') {
        RAM = &prog2;
        render(&cpu, *RAM);
      } else if (c == '3') {
        RAM = &prog3;
        render(&cpu, *RAM);
      }
      else if (c == 'q') return;
    }

    if(cpu.halt) {
      Sleep(100);
    } else {
      step(&cpu, *RAM);
      Sleep(sleep_delay);
    }
  }

}
