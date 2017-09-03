#include <inttypes.h>

#include "ben.h"

const uint32_t u_instructions[256][16] = {
  [NOP   ] = { MI|PO,  RO|II|CE,  0,          0,              0,      DR},
  [INR_B ] = { MI|PO,  RO|II|CE,  BO|AI,      EC_I|EF|EO|AI,  AO|BI|DR },
  [DCR_B ] = { MI|PO,  RO|II|CE,  BO|AI,      EC_D|EF|EO|AI,  AO|BI|DR },
  [MVI_B ] = { MI|PO,  RO|II|CE,  PO|MI|CE,   RO|BI|DR },
  [INR_C ] = { MI|PO,  RO|II|CE,  CO|AI,      EC_I|EF|EO|AI,  AO|CI|DR },
  [DCR_C ] = { MI|PO,  RO|II|CE,  CO|AI,      EC_D|EF|EO|AI,  AO|CI|DR },
  [MVI_C ] = { MI|PO,  RO|II|CE,  PO|MI|CE,   RO|CI|DR },

  [RAL   ] = { MI|PO,  RO|II|CE, EC_L|EO|AI|DR },
  [RAR   ] = { MI|PO,  RO|II|CE, EC_R|EO|AI|DR },

  [CMA   ] = { MI|PO,  RO|II|CE, EC_C|EO|AI|DR },

  [STA   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|MI|CE, AO|RI|DR },
  [LDA   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|MI|CE, RO|AI|DR },
  [INR_A ] = { MI|PO,  RO|II|CE, EC_I|EF|EO|AI|DR },
  [DCR_A ] = { MI|PO,  RO|II|CE, EC_D|EF|EO|AI|DR },
  [MVI_A ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|AI|DR },

  [MOV_BC] = { MI|PO,  RO|II|CE, CO|BI|DR },
  [MOV_BA] = { MI|PO,  RO|II|CE, AO|BI|DR },
  [MOV_CB] = { MI|PO,  RO|II|CE, BO|CI|DR },
  [MOV_CA] = { MI|PO,  RO|II|CE, AO|CI|DR },

  [HLT   ] = { MI|PO,  RO|II|CE, HT },
  [MOV_AB] = { MI|PO,  RO|II|CE, BO|AI|DR },
  [MOV_AC] = { MI|PO,  RO|II|CE, CO|AI|DR },

  [ADD_B ] = { MI|PO,  RO|II|CE, BO|TI, EO|AI|EF|DR },
  [ADD_C ] = { MI|PO,  RO|II|CE, CO|TI, EO|AI|EF|DR },

  [SUB_B ] = { MI|PO,  RO|II|CE, BO|TI, EO|SU|AI|EF|DR },
  [SUB_C ] = { MI|PO,  RO|II|CE, CO|TI, EO|SU|AI|EF|DR },

  [ANA_B ] = { MI|PO,  RO|II|CE, BO|TI, EC_A|EO|AI|EF|DR },
  [ANA_C ] = { MI|PO,  RO|II|CE, CO|TI, EC_A|EO|AI|EF|DR },
  [XRA_B ] = { MI|PO,  RO|II|CE, BO|TI, EC_X|EO|AI|EF|DR },
  [XRA_C ] = { MI|PO,  RO|II|CE, CO|TI, EC_X|EO|AI|EF|DR },

  [ORA_B ] = { MI|PO,  RO|II|CE, BO|TI, EC_O|EO|AI|EF|DR },
  [ORA_C ] = { MI|PO,  RO|II|CE, CO|TI, EC_O|EO|AI|EF|DR },

  [JNZ   ] = { MI|PO,  RO|II|CE, JZ, PO|MI|CE, RO|JP|DR, CE, CE|DR },
  [JMP   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|JP|DR },
  [RET   ] = { MI|PO,  RO|II|CE, 0 },
  [_JZ   ] = { MI|PO,  RO|II|CE, JZ, CE, CE|DR, PO|MI|CE, RO|JP|DR },
  [CALL  ] = { MI|PO,  RO|II|CE, 0 },

  [_OUT  ] = { MI|PO,  RO|II|CE, AO|O3|CE|DR },
  [_IN   ] = { MI|PO,  RO|II|CE, 0 },

  [ANI   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|TI, EC_A|EO|AI|EF|DR },
  [XRI   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|TI, EC_X|EO|AI|EF|DR },

  [ORI   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|TI, EC_O|EO|AI|EF|DR },
  [_JM   ] = { MI|PO,  RO|II|CE, JS, CE, CE|DR, PO|MI|CE, RO|JP|DR },
};

const char *mne_labels[256] = {
  [NOP   ] = "NOP",
  [INR_B ] = "INR B",
  [DCR_B ] = "DCR B",
  [MVI_B ] = "MVI B",
  [INR_C ] = "INR C",
  [DCR_C ] = "DCR C",
  [MVI_C ] = "MVI C",

  [RAL   ] = "RAL",
  [RAR   ] = "RAR",

  [CMA   ] = "CMA",

  [STA   ] = "STA",
  [LDA   ] = "LDA",
  [INR_A ] = "INR A",
  [DCR_A ] = "DCR A",
  [MVI_A ] = "MVI A",

  [MOV_BC] = "MOV B,C",
  [MOV_BA] = "MOV B,A",
  [MOV_CB] = "MOV C,B",
  [MOV_CA] = "MOV C,A",

  [HLT   ] = "HLT",
  [MOV_AB] = "MOV A,B",
  [MOV_AC] = "MOV A,C",

  [ADD_B ] = "ADD B",
  [ADD_C ] = "ADD C",

  [SUB_B ] = "SUB B",
  [SUB_C ] = "SUB C",

  [ANA_B ] = "ANA B",
  [ANA_C ] = "ANA C",
  [XRA_B ] = "XRA B",
  [XRA_C ] = "XRA C",

  [ORA_B ] = "ORA B",
  [ORA_C ] = "ORA C",

  [JNZ   ] = "JNZ",
  [JMP   ] = "JMP",
  [RET   ] = "RET",
  [_JZ   ] = "JZ",
  [CALL  ] = "CALL",

  [_OUT  ] = "OUT",
  [_IN   ] = "IN",

  [ANI   ] = "ANI",
  [XRI   ] = "XRI",

  [ORI   ] = "ORI",
  [_JM   ] = "JM",
};
