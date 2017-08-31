#define REGISTER_A_X  46
#define REGISTER_A_Y   3
#define ALU_X         REGISTER_A_X + 2
#define ALU_Y         REGISTER_A_Y + 4
#define REGISTER_TMP_X  REGISTER_A_X
#define REGISTER_TMP_Y  ALU_Y + 3
#define REGISTER_B_X  REGISTER_A_X
#define REGISTER_B_Y  REGISTER_TMP_Y + 3
#define CLOCK_X        2
#define CLOCK_Y        1
#define COUNTER_X     CLOCK_X
#define COUNTER_Y     CLOCK_Y + 3
#define BUS_X         28
#define BUS_Y         CLOCK_Y
#define RAM_X         COUNTER_X
#define RAM_Y         COUNTER_Y + 3
#define OUTPUT_X      REGISTER_A_X
#define OUTPUT_Y      REGISTER_B_Y + 3
#define INSTRUCTION_X COUNTER_X
#define INSTRUCTION_Y RAM_Y + 4
#define DECODER_X     COUNTER_X
#define DECODER_Y     INSTRUCTION_Y + 4
#define CONTROL_X     COUNTER_X
#define CONTROL_Y     DECODER_Y + 3
#define HELP_X         1
#define HELP_Y        CONTROL_Y + 4
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

void updateDisplay(const CPU *, const ram_type);

void printRegisterA(const CPU *);
void printRegisterB(const CPU *);
void printRegisterTMP(const CPU *);
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
