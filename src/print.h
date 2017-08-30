#define REGISTER_A_X  46
#define REGISTER_A_Y   6
#define REGISTER_B_X  REGISTER_A_X
#define REGISTER_B_Y  12
#define ALU_X         REGISTER_A_X + 2
#define ALU_Y          9
#define COUNTER_X     REGISTER_A_X
#define COUNTER_Y      3
#define BUS_X         28
#define BUS_Y          1
#define CLOCK_X        2
#define CLOCK_Y        1
#define RAM_X          2
#define RAM_Y          4
#define OUTPUT_X      REGISTER_A_X
#define OUTPUT_Y      15
#define INSTRUCTION_X  2
#define INSTRUCTION_Y  8
#define DECODER_X      2
#define DECODER_Y     12
#define CONTROL_X      2
#define CONTROL_Y     19
#define HELP_X         1
#define HELP_Y        22
#define RAM_MAP_X     REGISTER_A_X + 16
#define RAM_MAP_Y      1

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
void printRegister16();

void printLabels();

void printRegisterA(const CPU *);
void printRegisterB(const CPU *);
void printALU(const CPU *);
void printProgramCounter(const CPU *);
void printBus(const CPU *);
void printRam(const CPU *, const ram_type);
void printOutput(const CPU *);
void printInstruction(const CPU *);
void printDecoder(const CPU *);
void printControl(const CPU *);
void printClock(const CPU *);
void printRamMap(const CPU *, const ram_type);
void printBusGraphic(const CPU *);
