#include <inttypes.h>

#include "ben.h"

const uint32_t u_instructions[256][16] = {
  [NOP]    = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [INR_B]  = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [DCR_B]  = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [MVI_B]  = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [INR_C]  = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [DCR_C]  = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [MVI_C]  = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
};
