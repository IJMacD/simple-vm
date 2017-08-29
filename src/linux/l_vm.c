#include <unistd.h>
#include <stdio.h>

#include "../vm.h"

void print_output(unsigned char reg) {
  printf("%3d\n", reg);
}

int main() {

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

  ram_type RAM = PRGRM_3;
  unsigned int sleep_delay = DEFAULT_SLEEP;

  output_hook = print_output;

  while(1){
    step(&cpu, RAM);

    usleep(sleep_delay*1000);
  }
}
