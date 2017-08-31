#include <inttypes.h>

#include "ben.h"

const uint32_t u_instructions[256][16] = {
  [NOP   ] = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [INR_B ] = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [DCR_B ] = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [MVI_B ] = { MI|PO,  RO|II|CE,  PO|MI|CE,      RO|BI|DR,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [INR_C ] = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [DCR_C ] = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },
  [MVI_C ] = { MI|PO,  RO|II|CE,  0,      0,      0,         0, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0 },

  [RAL   ] = { MI|PO,  RO|II|CE, 0 },
  [RAR   ] = { MI|PO,  RO|II|CE, 0 },

  [CMA   ] = { MI|PO,  RO|II|CE, 0 },

  [STA   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|MI|CE, AO|RI|DR },
  [LDA   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|MI|CE, RO|AI|DR },
  [INR_A ] = { MI|PO,  RO|II|CE, 0 },
  [DCR_A ] = { MI|PO,  RO|II|CE, 0 },
  [MVI_A ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|AI|DR },

  [MOV_BC] = { MI|PO,  RO|II|CE, 0 },
  [MOV_BA] = { MI|PO,  RO|II|CE, AO|BI|DR },
  [MOV_CB] = { MI|PO,  RO|II|CE, 0 },
  [MOV_CA] = { MI|PO,  RO|II|CE, 0 },

  [HLT   ] = { MI|PO,  RO|II|CE, HT },
  [MOV_AB] = { MI|PO,  RO|II|CE, 0 },
  [MOV_AC] = { MI|PO,  RO|II|CE, 0 },

  [ADD_B ] = { MI|PO,  RO|II|CE, BO|TI, EO|AI|DR },
  [ADD_C ] = { MI|PO,  RO|II|CE, CO|TI, EO|AI|DR },

  [SUB_B ] = { MI|PO,  RO|II|CE, BO|TI, EO|SU|AI|DR },
  [SUB_C ] = { MI|PO,  RO|II|CE, CO|TI, EO|SU|AI|DR },

  [ANA_B ] = { MI|PO,  RO|II|CE, 0 },
  [ANA_C ] = { MI|PO,  RO|II|CE, 0 },
  [XRA_B ] = { MI|PO,  RO|II|CE, 0 },
  [XRA_C ] = { MI|PO,  RO|II|CE, 0 },

  [ORA_B ] = { MI|PO,  RO|II|CE, 0 },
  [ORA_C ] = { MI|PO,  RO|II|CE, 0 },

  [JNZ   ] = { MI|PO,  RO|II|CE, 0 },
  [JMP   ] = { MI|PO,  RO|II|CE, PO|MI|CE, RO|JP|DR },
  [RET   ] = { MI|PO,  RO|II|CE, 0 },
  [JZ    ] = { MI|PO,  RO|II|CE, 0 },
  [CALL  ] = { MI|PO,  RO|II|CE, 0 },

  [_OUT  ] = { MI|PO,  RO|II|CE, AO|O3|CE|DR },
  [_IN   ] = { MI|PO,  RO|II|CE, 0 },

  [ANI   ] = { MI|PO,  RO|II|CE, 0 },
  [XRI   ] = { MI|PO,  RO|II|CE, 0 },

  [ORI   ] = { MI|PO,  RO|II|CE, 0 },
  [JM    ] = { MI|PO,  RO|II|CE, 0 },
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
  [JZ    ] = "JZ",
  [CALL  ] = "CALL",

  [_OUT  ] = "OUT",
  [_IN   ] = "IN",

  [ANI   ] = "ANI",
  [XRI   ] = "XRI",

  [ORI   ] = "ORI",
  [JM    ] = "JM",
};
