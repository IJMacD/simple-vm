#include <unistd.h>
#include <stdio.h>

#include "../vm.h"

void print_output(unsigned char reg) {
  printf("%3d\n", reg);
}

int main() {
  output_hook = print_output;

  decodeInstruction(&cpu);
  updateDisplay(&cpu);

  usleep(sleep_delay*1000);

  // step();

  while(1){
    step(&cpu);

    usleep(sleep_delay*1000);
  }
}
