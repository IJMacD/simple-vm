#include <windows.h>

#include "../vm.h"

/*   vm.h    */
extern unsigned char halt;
extern unsigned int sleep_delay;

void *hConsole;

void main() {
  // Create blank console
  hConsole =  CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  SetConsoleOutputCP(437); // DOS
  // SetConsoleOutputCP(1252); // Windows-1252 ANSI Latin 1
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

    if(_kbhit()) {
      char c = _getch();
      if(c == ' ') step();
      else if(c == 'r') reset();
      else if(c == 'a') {
        halt = halt ? 0 : 1;
        printClock();
      } else if (c == 'f') {
        sleep_delay /= 2;
        if (sleep_delay < 10) sleep_delay = 10;
      } else if (c == 's') {
        sleep_delay *= 2;
      }
      else if (c == 'q') return;
    }

    if(halt) {
      Sleep(100);
    } else {
      step();
      Sleep(sleep_delay);
    }
  }

}
