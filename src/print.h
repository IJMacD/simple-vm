#define REGISTER_A_X  50
#define REGISTER_A_Y   4
#define REGISTER_B_X  50
#define REGISTER_B_Y  10
#define ALU_X         52
#define ALU_Y          7
#define COUNTER_X     50
#define COUNTER_Y      1
#define BUS_X         29
#define BUS_Y          1
#define CLOCK_X        2
#define CLOCK_Y        1
#define RAM_X          2
#define RAM_Y          4
#define OUTPUT_X      50
#define OUTPUT_Y      13
#define INSTRUCTION_X  2
#define INSTRUCTION_Y  8
#define DECODER_X      2
#define DECODER_Y     12
#define CONTROL_X      8
#define CONTROL_Y     18
#define HELP_X         4
#define HELP_Y        22

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

void printRegister4();
void printRegister8();
void printRegisterA();
void printRegisterB();
void printALU();
void printProgramCounter();
void printBus();
void printRam();
void printOutput();
void printInstruction();
void printDecoder();
void printControl();
void printClock();
